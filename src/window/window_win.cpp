#include <flyingwhales/window/window_win.hpp>
#include <sstream>
#include <algorithm>
#include <boost/locale.hpp>

namespace fw
{

	const Size2 WindowWin::_minimum_size = Size2(128, 128);

	WindowWin::WindowClass::WindowClass(const HINSTANCE &instance)
		: _class{ 0 }
	{
		{
			std::wstringstream ss;
			ss << "fw::WindowWin::WindowClass";
			ss << "@0x";
			ss << std::hex << this;
			_name = ss.str();
		}

		_class.cbSize = sizeof(WNDCLASSEX);
		_class.hInstance = instance;
		_class.lpszClassName = _name.data();
		_class.lpfnWndProc = _window_proc;
		_class.style = CS_HREDRAW | CS_VREDRAW;
		_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		_class.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME;

		if (!RegisterClassExW(&_class))
			throw Exception("Failed to register Win32 window class");
	}

	WindowWin::WindowClass::~WindowClass()
	{
		UnregisterClassW(_class.lpszClassName, _class.hInstance);
	}

	const WNDCLASSEXW &WindowWin::WindowClass::get_class() const
	{
		return _class;
	}

	LRESULT CALLBACK WindowWin::_window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam)
	{
		auto win = reinterpret_cast<WindowWin *>(GetWindowLongPtrW(window, GWLP_USERDATA));
		if (win != nullptr)
		{
			switch (message)
			{
				// stop being able to resize below minimum size
			case WM_GETMINMAXINFO:
			{
				auto info = (LPMINMAXINFO)lparam;
				info->ptMinTrackSize.x = _minimum_size.x;
				info->ptMinTrackSize.y = _minimum_size.y;
				break;
			}
			case WM_CLOSE:
			case WM_DESTROY:
			case WM_QUIT:
				win->_messages.push(WindowMessage{ WindowMessage::Type::Close });
				break;
			case WM_SIZE:
				win->set_size(Size2(LOWORD(lparam), HIWORD(lparam)));
				if (win->_messages.empty() || (win->_messages.back().type != WindowMessage::Type::Resize))
					win->_messages.push(WindowMessage{ WindowMessage::Type::Resize });
				break;
			case WM_MOUSEMOVE:
				win->_mouse_position.x = LOWORD(lparam);
				win->_mouse_position.y = HIWORD(lparam);
				if (win->_messages.empty() || (win->_messages.back().type != WindowMessage::Type::MouseMove))
					win->_messages.push(WindowMessage{ WindowMessage::Type::MouseMove });
				break;
			case WM_SETFOCUS:
				win->_focus = true;
				win->_messages.push(WindowMessage{ WindowMessage::Type::FocusGained });
				break;
			case WM_KILLFOCUS:
				win->_focus = false;
				win->_messages.push(WindowMessage{ WindowMessage::Type::FocusLost });
				break;
			case WM_SHOWWINDOW:
				if (wparam)
				{
					win->_visible = true;
					win->_messages.push(WindowMessage{ WindowMessage::Type::Shown });
				}
				else
				{
					win->_visible = false;
					win->_messages.push(WindowMessage{ WindowMessage::Type::Hidden });
				}
			}
		}

		return DefWindowProcW(window, message, wparam, lparam);
	}

	WindowWin::WindowWin(const std::string &title, const fw::Size2 &size)
		: _instance(GetModuleHandle(nullptr)),
		_window_class(_instance),
		_title(title),
		_size(size)
	{
		_window_handle = CreateWindowW(
			_window_class.get_class().lpszClassName,
			_window_class.get_class().lpszClassName,
			WS_OVERLAPPEDWINDOW,
			0,
			0,
			_size.x,
			_size.y,
			nullptr,
			nullptr,
			_instance,
			nullptr
		);

		if (!_window_handle)
			throw Exception("Failed to create Win32 window");

		_style = GetWindowLongPtrW(_window_handle, GWL_STYLE);
		_style_ex = GetWindowLongPtrW(_window_handle, GWL_EXSTYLE);
		SetWindowLongPtrW(_window_handle, GWLP_USERDATA, (DWORD_PTR)this);

		// ensure state
		set_visible(false);
		set_title(_title);
		set_size(_size);
	}

	WindowWin::~WindowWin()
	{
		DestroyWindow(_window_handle);
	}

	bool WindowWin::poll_messages(WindowMessage &message)
	{
		while (PeekMessageW(&_window_message, _window_handle, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&_window_message);
			DispatchMessageW(&_window_message);
		}

		while (!_messages.empty())
		{
			message = _messages.front();
			_messages.pop();
			return true;
		}

		return false;
	}


	bool WindowWin::get_visible() const
	{
		return _visible;
	}

	void WindowWin::set_visible(bool visible)
	{
		_visible = visible;
		ShowWindow(_window_handle, _visible ? SW_SHOW : SW_HIDE);
	}

	const std::string &WindowWin::get_title() const
	{
		return _title;
	}

	void WindowWin::set_title(const std::string &title)
	{
		_title = title;
		auto wtitle = boost::locale::conv::utf_to_utf<wchar_t>(_title);
		SetWindowTextW(_window_handle, wtitle.c_str());
	}

	const Size2 &WindowWin::get_size() const
	{
		return _size;
	}

	void WindowWin::set_size(const Size2 &size)
	{
		// clamp above minimum size
		_size = Size2(std::max(size.x, _minimum_size.x), std::max(size.y, _minimum_size.y));

		RECT client_rect;
		GetClientRect(_window_handle, &client_rect);
		client_rect.right = client_rect.left + _size.x;
		client_rect.bottom = client_rect.top + _size.y;
		AdjustWindowRectEx(&client_rect, (DWORD)_style, false, (DWORD)_style_ex);

		SetWindowPos(
			_window_handle,
			nullptr,
			0,
			0,
			client_rect.right - client_rect.left,
			client_rect.bottom - client_rect.top,
			SWP_NOMOVE | SWP_NOZORDER
		);
	}

	const Size2 &WindowWin::get_mouse_position() const
	{
		return _mouse_position;
	}

	void WindowWin::set_mouse_position(const Size2 &position)
	{
		_mouse_position = position;

		POINT point{ (LONG)_mouse_position.x, (LONG)_mouse_position.y };
		ClientToScreen(_window_handle, &point);
		SetCursorPos(point.x, point.y);
	}

	bool WindowWin::get_focus() const
	{
		return _focus;
	}

	void WindowWin::set_focus(bool focus)
	{
		_focus = focus;
		SetFocus(_focus ? _window_handle : nullptr);
	}

}
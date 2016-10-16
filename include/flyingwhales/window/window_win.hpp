#pragma once

#include <flyingwhales/window/window_interface.hpp>
#include <queue>

namespace fw
{

	class WindowWin : public WindowInterface
	{
	private:
		class WindowClass : protected Noncopyable
		{
		private:
			std::wstring _name;
			WNDCLASSEXW _class;
		public:
			WindowClass(const HINSTANCE &instance);
			~WindowClass();

			const WNDCLASSEXW &get_class() const;
		};

		static const Size2 _minimum_size;

		HINSTANCE _instance;
		WindowClass _window_class;
		HWND _window_handle;
		MSG _window_message;
		LONG_PTR _style;
		LONG_PTR _style_ex;

		std::string _title;
		bool _visible;
		Size2 _size;
		Size2 _mouse_position;
		bool _focus;

		std::queue<WindowMessage> _messages;
	private:
		static LRESULT CALLBACK _window_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
	public:
		WindowWin(const std::string &title, const Size2 &size);
		~WindowWin();

		bool poll_messages(WindowMessage &message) override;

		bool get_visible() const override;
		void set_visible(bool visible) override;

		const std::string &get_title() const override;
		void set_title(const std::string &title) override;

		const Size2 &get_size() const override;
		void set_size(const Size2 &size) override;

		const Size2 &get_mouse_position() const override;
		void set_mouse_position(const Size2 &position) override;

		bool get_focus() const override;
		void set_focus() override;
	};

}
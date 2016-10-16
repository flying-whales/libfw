#pragma once

#include <flyingwhales/maths.hpp>
#include <flyingwhales/core.hpp>
#include <string>

namespace fw
{
	
	class WindowMessage
	{
	public:
		enum class Type : uint8_t
		{
			Close,
			Resize,
			MouseMove,
			FocusLost,
			FocusGained,
			Shown,
			Hidden
		};
	public:
		Type type;
	};

	class WindowInterface : protected Noncopyable
	{
	public:
		virtual ~WindowInterface() = default;

		virtual bool poll_messages(WindowMessage &message) = 0;

		virtual bool get_visible() const = 0;
		virtual void set_visible(bool visible) = 0;

		virtual const std::string &get_title() const = 0;
		virtual void set_title(const std::string &title) = 0;

		virtual const Size2 &get_size() const = 0;
		virtual void set_size(const Size2 &size) = 0;

		virtual const Size2 &get_mouse_position() const = 0;
		virtual void set_mouse_position(const Size2 &position) = 0;

		virtual bool get_focus() const = 0;
		virtual void set_focus(bool focus) = 0;
	};

}

#define FW_WINDOW_CONSTRUCTOR_SYMBOLS const std::string &, const fw::Size2 &
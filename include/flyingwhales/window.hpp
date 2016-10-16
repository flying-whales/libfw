#pragma once

#include <flyingwhales/core.hpp>

#ifdef FW_PLATFORM_WIN
#include <flyingwhales/window/window_win.hpp>
namespace fw { using Window = WindowWin; }
#else
#error Platform is not supported
#endif

#include <flyingwhales/window/window_interface.hpp>
#include <type_traits>

namespace fw
{
	static_assert(std::is_base_of<WindowInterface, Window>::value, "Window is not a base class of WindowInterface");
	static_assert(std::is_constructible<Window, FW_WINDOW_CONSTRUCTOR_SYMBOLS>::value, "Window is missing a valid constructor");
}
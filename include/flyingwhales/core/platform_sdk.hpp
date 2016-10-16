#pragma once

#include <flyingwhales/core/platform.hpp>

#ifdef FW_PLATFORM_WIN
#	define WIN32_LEAN_AND_MEAN
#	define VC_EXTRA_LEAN
#	define NOMINMAX
#	include <Windows.h>
#	undef near
#	undef far
#endif
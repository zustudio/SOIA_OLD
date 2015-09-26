
#pragma once

#include "OpenGL.h"

namespace Environment
{
	enum class EKeyModifier : int
	{
		None = 0,

		Shift = GLFW_MOD_SHIFT,
		Control = GLFW_MOD_CONTROL,
		Alt = GLFW_MOD_ALT,

		ShiftControl = GLFW_MOD_SHIFT | GLFW_MOD_CONTROL,
		ControlAlt = GLFW_MOD_CONTROL | GLFW_MOD_ALT,
		ShiftAlt = GLFW_MOD_SHIFT | GLFW_MOD_ALT,

		ShiftControlAlt = GLFW_MOD_SHIFT | GLFW_MOD_CONTROL | GLFW_MOD_ALT,

		Super = GLFW_MOD_SUPER
	};

	enum class EKeyAction : int
	{
		Press = GLFW_PRESS,
		Release = GLFW_RELEASE,
		Repeat = GLFW_REPEAT
	};

	enum class EMouseButton : int
	{
		Left = GLFW_MOUSE_BUTTON_LEFT,
		Middle = GLFW_MOUSE_BUTTON_MIDDLE,
		Right = GLFW_MOUSE_BUTTON_RIGHT
	};
}
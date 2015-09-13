
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

	class EventInfo_KeyChanged
	{
	public:
		EventInfo_KeyChanged(int InKey, int InScanCode, int InAction, int InMods);
		EventInfo_KeyChanged(int InKey, EKeyModifier InKeyModifier = EKeyModifier::None, EKeyAction InKeyAction = EKeyAction::Press);

		bool operator==(EventInfo_KeyChanged const & InOther);

		int Key;
		int ScanCode;
		int Action;
		int Mods;
	};
}
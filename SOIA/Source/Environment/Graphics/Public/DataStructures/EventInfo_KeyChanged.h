
#pragma once

#include "OpenGL.h"
#include "GLFWMacroEnums.h"

namespace Environment
{

	class LIBIMPEXP EventInfo_KeyChanged
	{
	public:
		EventInfo_KeyChanged(int InKey, int InScanCode, int InAction, int InMods);
		EventInfo_KeyChanged(int InKey, EKeyModifier InKeyModifier = EKeyModifier::None, EKeyAction InKeyAction = EKeyAction::Press);

		bool operator==(EventInfo_KeyChanged const & InOther) const;

		int Key;
		int ScanCode;
		int Action;
		int Mods;
	};
}
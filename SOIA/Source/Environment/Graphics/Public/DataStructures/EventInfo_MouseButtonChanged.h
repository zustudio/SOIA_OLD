
#pragma once

#include "OpenGL.h"
#include "GLFWMacroEnums.h"

namespace Environment
{
	class LIBIMPEXP EventInfo_MouseButtonChanged
	{
	public:
		EventInfo_MouseButtonChanged(int InButton, int InAction, int InMod);
		EventInfo_MouseButtonChanged(EMouseButton InButton, EKeyModifier InKeyModifier = EKeyModifier::None, EKeyAction InKeyAction = EKeyAction::Press);

		bool operator==(EventInfo_MouseButtonChanged const & InOther) const;

		EMouseButton Button;
		EKeyAction Action;
		EKeyModifier Mod;
	};
}

#include "Definitions.h"

#include "EventInfo_MouseButtonChanged.h"
using namespace Env;

Environment::EventInfo_MouseButtonChanged::EventInfo_MouseButtonChanged(int InButton, int InAction, int InMod)
	:
	Button(EMouseButton(InButton)),
	Mod(EKeyModifier(InMod)),
	Action(EKeyAction(InAction))
{}

EventInfo_MouseButtonChanged::EventInfo_MouseButtonChanged(EMouseButton InMouseButton, EKeyModifier InKeyModifier, EKeyAction InKeyAction)
	:
	Button(InMouseButton),
	Mod(InKeyModifier),
	Action(InKeyAction)
{}



bool EventInfo_MouseButtonChanged::operator==(EventInfo_MouseButtonChanged const & InOther) const
{
	return false;
}

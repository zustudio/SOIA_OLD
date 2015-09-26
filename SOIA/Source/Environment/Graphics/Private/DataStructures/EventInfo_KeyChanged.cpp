
#include "Definitions.h"

#include "EventInfo_KeyChanged.h"
using namespace Environment;

EventInfo_KeyChanged::EventInfo_KeyChanged(int InKey, int InScanCode, int InAction, int InMods)
	:
	Key(InKey),
	ScanCode(InScanCode),
	Action(InAction),
	Mods(InMods)
{}

EventInfo_KeyChanged::EventInfo_KeyChanged(int InKey, EKeyModifier InKeyModifier, EKeyAction InKeyAction)
	:
	Key(InKey),
	ScanCode(-1),
	Action(int(InKeyAction)),
	Mods(int(InKeyModifier))
{}

bool EventInfo_KeyChanged::operator==(EventInfo_KeyChanged const & InOther) const
{
	bool equal = true;

	equal &= Action == InOther.Action;
	equal &= Mods == InOther.Mods;
	if (Key >= 0 && InOther.Key >= 0)
		equal &= Key == InOther.Key;
	if (ScanCode >= 0 && InOther.ScanCode >= 0)
		equal &= ScanCode == InOther.ScanCode;

	return equal;
}

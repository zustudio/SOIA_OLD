
#include "Definitions.h"

#include "EventInfo_SelectionChanged.h"
using namespace Environment;

EventInfo_SelectionChanged::EventInfo_SelectionChanged(ESelectionStatus InSelectionStatus)
	:
	SelectionStatus(InSelectionStatus)
{}

bool Environment::EventInfo_SelectionChanged::operator==(ESelectionStatus const & InOther) const
{
	return SelectionStatus == InOther;
}

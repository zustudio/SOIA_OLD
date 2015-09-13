
#pragma once

namespace Environment
{
	enum class ESelectionStatus
	{
		Selected,
		Unselected
	};

	class EventInfo_SelectionChanged
	{
	public:
		EventInfo_SelectionChanged(ESelectionStatus InSelectionStatus);

		bool operator==(ESelectionStatus const & InOther);

	private:
		ESelectionStatus SelectionStatus;
	};
}
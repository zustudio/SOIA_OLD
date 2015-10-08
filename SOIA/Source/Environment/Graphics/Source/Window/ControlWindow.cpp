
#include "Definitions.h"

#include "ControlWindow.h"
using namespace Environment;

#include "FreeTypeProvider.h"
#include "Directory.h"
#include "GlobalStyle.h"

ControlWindow::ControlWindow(std::string Name, pxSize InSize)
	:
	GraphicsWindow(Name, InSize),
	ContentArea(new WindowArea(
		this,
		pxMargins(0, 0, 0, 0),
		GlobalStyle())),
	Index_SelectedControl(0)
{
}

void ControlWindow::Event_KeyChanged(EventInfo_KeyChanged const & InInfo)
{
	bool selectingControl = false;
	bool selectDirection = false;
	if (InInfo == EventInfo_KeyChanged(GLFW_KEY_TAB, EKeyModifier::Control))
	{
		selectingControl = true;
		selectDirection = true;
	}
	else if (InInfo == EventInfo_KeyChanged(GLFW_KEY_TAB, EKeyModifier::ShiftControl))
	{
		selectingControl = true;
		selectDirection = false;
	}

	if (selectingControl)
	{
		GetSelectedControl()->Event_SelectionChanged(EventInfo_SelectionChanged(ESelectionStatus::Unselected));
		SelectNextControl(selectDirection);
		GetSelectedControl()->Event_SelectionChanged(EventInfo_SelectionChanged(ESelectionStatus::Selected));
	}
	else
	{
		GetSelectedControl()->Event_KeyChanged(InInfo);
	}
}

void ControlWindow::Event_CharacterEntered(unsigned int InChar)
{
	GetSelectedControl()->Event_CharacterEntered(InChar);
}

void ControlWindow::Event_MouseButtonChanged(EventInfo_MouseButtonChanged const & InInfo)
{
	std::cout << "Mouse pressed: " << std::to_string(int(InInfo.Button)) << std::endl;
}
void ControlWindow::Event_Scroll(Vector2D<double> const & InOffset)
{
	GetSelectedControl()->Event_Scroll(InOffset);
}

void ControlWindow::SelectNextControl(bool bForward)
{
	int step = (int(bForward) * 2 - 1);
	int index_SelectedControl = Index_SelectedControl;
	int size = GetControls().size();
	
	index_SelectedControl += step;
	if (index_SelectedControl == -1 || index_SelectedControl == size)
	{
		index_SelectedControl = size - step * index_SelectedControl;
	}
	Index_SelectedControl = index_SelectedControl;
}

GraphicsControl * ControlWindow::GetSelectedControl()
{
	return GetControls()[Index_SelectedControl];
}

std::vector<GraphicsControl*> ControlWindow::GetControls()
{
	std::vector<MBound*> const & objects = ContentArea->GetBoundObjects();
	std::vector<GraphicsControl*> result;
	
	for (MBound* object : objects)
	{
		GraphicsControl* control = dynamic_cast<GraphicsControl*>(object);
		if (control)
			result.push_back(control);
	}
	return result;
}

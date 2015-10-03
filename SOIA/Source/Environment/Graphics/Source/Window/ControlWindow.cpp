
#include "Definitions.h"

#include "ControlWindow.h"
using namespace Environment;

#include "FreeTypeProvider.h"
#include "Directory.h"

ControlWindow::ControlWindow(std::string Name, pxSize InSize)
	: GraphicsWindow(Name, InSize),
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
	std::cout << "Mouse scrolled: " << std::to_string(InOffset.Y) << std::endl;

	pxPoint delta;
	delta.X = InOffset.X * 7;
	delta.Y = InOffset.Y * -7;
	
	GetSelectedControl()->Scroll(delta);
}

void ControlWindow::SelectNextControl(bool bForward)
{
	int step = (int(bForward) * 2 - 1);
	int index_SelectedControl = Index_SelectedControl;

	GraphicsControl* newControl = nullptr;
	do
	{
		index_SelectedControl += step;
		if (index_SelectedControl == -1 || index_SelectedControl == GetBoundObjects().size())
		{
			index_SelectedControl = GetBoundObjects().size() - step * index_SelectedControl;
		}
		newControl = dynamic_cast<GraphicsControl*>(GetBoundObjects()[index_SelectedControl]);
	} while (!newControl);
	Index_SelectedControl = index_SelectedControl;
}

GraphicsControl * ControlWindow::GetSelectedControl()
{
	return (GraphicsControl*)GetBoundObjects()[Index_SelectedControl];
}

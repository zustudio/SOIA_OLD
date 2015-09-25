
#include "Definitions.h"

#include "ControlWindow.h"
using namespace Environment;

#include "FreeTypeProvider.h"
#include "Directory.h"

ControlWindow::ControlWindow(std::string Name, pxSize InSize)
	: GraphicsWindow(Name, InSize),
	Index_SelectedControl(0),
	CommonTextContentLayer(TextLayer(*GetFont(Directory::ExecutableDirectory().GetPath().AppendFolder("Ressources").AppendFolder("Fonts").AppendFolder("DengXian").AppendFile("DengXian.ttf").ToString()), 15))
{
	AddLayer(&CommonFilledGeometryLayer);
	AddLayer(&CommonUnfilledGeometryLayer);
	AddLayer(&CommonTextContentLayer);
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

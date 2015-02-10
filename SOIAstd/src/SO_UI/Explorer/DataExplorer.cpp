
#include "stdafx.h"

#include "DEGraph.h"
#include "DataExplorer.h"

#include "Draw_2D.h"

using namespace SO::UI;
using namespace SO::Com;
using namespace SO::Drawing;

DataExplorer::DataExplorer(IA::Engine* NewEngine, ComService* NewUp, SO::MeaningStream::MeaningService* MSrvc) : Window(std::string("DataExplorer")), IIComIO(NewUp)
{
	//init vars
	CurrentEngine = NewEngine;
	Drawable = new Draw_2D();
	MeaningSrvc = MSrvc;
	DrawnSet = "SDLcreated";

	//create window
	TopTextBox = new CTextBox(this, cPoint(0, 0, 0, 0), cPoint(1, 0, 0, 50));
	Canvas = new CCanvas(this, cPoint(0,0,0,50), cPoint(1,1,0,-50));
	myControls.push_back(Canvas);
	myControls.push_back(TopTextBox);

	//initial drawing
	cmd_redraw(Handle<ICom>(this, ""), std::vector<VoidPointer>());
	
}

void DataExplorer::Tick()
{
	Window::Tick();
}


//////////////////////////////////////////////////////////////////////
// ICom
Handle<ICom>& DataExplorer::cGetHandle()
{
	TryCreateHandle("DataExplorer");
	return IIComIO::cGetHandle();
}
void DataExplorer::cGetCommands(std::vector<Handle<ICmd> > &Commands)
{
	ICom_RegisterCmd(Commands, DataExplorer, cmd_redraw, "redraw");
	ICom_RegisterCmd(Commands, DataExplorer, cmd_redraw, "redraw");

}
//////////////////////////////////////////////////////////////////////
// commands
bool DataExplorer::cmd_redraw(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	bool result = false;
	Handle<ExDSet> set = MeaningSrvc->GetSetByName(DrawnSet);

	if (set.getObj())
	{
		Drawable->Draw(Canvas, set.getObj()->GetGroups());
		TopTextBox->Text = "Currently drawn data set: " + set.getName() + "\n    - Number of groups: " + std::to_string(set.getObj()->GetGroups()->size()) + '\n';
		result = true;
	}
	return result;
}
bool DataExplorer::cmd_setset(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	bool result = false;

	if (Args.size() > 0)
	{
		std::string* setName = Args[0].CastTo<std::string>();
		if (setName)
		{
			DrawnSet = *setName;
			result = true;
		}
	}
	return result;
}
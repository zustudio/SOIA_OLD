
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

	//create window
	TopTextBox = new CTextBox(this, cPoint(0, 0, 0, 0), cPoint(1, 0, 0, 50));
	Canvas = new CCanvas(this, cPoint(0,0,0,50), cPoint(1,1,0,-50));
	myControls.push_back(Canvas);
	myControls.push_back(TopTextBox);



	Handle<ExDSet> set = MeaningSrvc->GetSetByName("SDLcreated");


	Drawable->Draw(Canvas, set.getObj()->GetGroups());
	TopTextBox->Text = "Currently drawn data set: " + set.getName() + "\n    - Number of groups: " + std::to_string(set.getObj()->GetGroups()->size()) + '\n';
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

}

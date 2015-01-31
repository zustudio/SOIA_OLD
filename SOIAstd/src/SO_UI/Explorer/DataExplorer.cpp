
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
	Canvas = new CCanvas(this, fPoint(), fPoint(1, 1));
	myControls.push_back(Canvas);



	Handle<ExDSet> set = MeaningSrvc->DataSets[0];


	Drawable->Draw(Canvas, set.getObj()->GetGroups());
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


#include "stdafx.h"

#include "DEGraph.h"
#include "DataExplorer.h"

using namespace SO::UI;
using namespace SO::Com;

DataExplorer::DataExplorer(IA::Engine* NewEngine, ComService* NewUp) : Window(std::string("DataExplorer")), IIComIO(NewUp)
{
	//init vars
	CurrentEngine = NewEngine;

	//create window
	myDEGraph = new DEGraph(CurrentEngine->getDataStart(), this, fPoint(), fPoint(1, 1));
	myControls.push_back(myDEGraph);
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

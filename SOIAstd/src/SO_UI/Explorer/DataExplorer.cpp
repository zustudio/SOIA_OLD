
#include "stdafx.h"

#include "DEGraph.h"
#include "DataExplorer.h"

using namespace SO::UI;

DataExplorer::DataExplorer(IA::Engine* NewEngine) : Window(std::string("DataExplorer"))
{
	//init vars
	CurrentEngine = NewEngine;

	//create window
	myDEGraph = new DEGraph(CurrentEngine->getDataStart(), this, fPoint(), fPoint(1, 1));
	myControls.push_back(myDEGraph);
}

void DataExplorer::Start()
{
	Window::Start();
}

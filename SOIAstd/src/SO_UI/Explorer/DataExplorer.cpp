
#include <string>

#include "Data.h"
#include "Engine.h"
#include "fPoint.h"
#include "CCanvas.h"
#include "DEGraph.h"
#include "DataExplorer.h"

using namespace SO::UI;

DataExplorer::DataExplorer(IA::Engine* NewEngine) : Window(std::string("DataExplorer"))
{
	//init vars
	CurrentEngine = NewEngine;

	//create window
	myDEGraph = new DEGraph(CurrentEngine->Knowledge, this, fPoint(), fPoint(1, 1));
	myControls.push_back(myDEGraph);
}

void DataExplorer::Start()
{
	Window::Start();
}
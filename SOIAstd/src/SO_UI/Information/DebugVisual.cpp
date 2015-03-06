
#include "stdafx.h"
#include "SDL.h"

#include "CTextBox.h"
#include "CGraph.h"
#include "DebugVisual.h"
#include "Statistics.h"


SDL_Modules_Init

using namespace SO::UI;
using namespace SO::Com;
using namespace SO::Debug;
using namespace IA;

/////////////////////////////////////////////////////////////////////////////////////
// init
DebugVisual::DebugVisual(IA::Engine* NewEngine, SO::Com::ComService* NewUp) : Window(std::string("DebugVisual")), IIComIO(NewUp)
{
	//init vars
	CurrentEngine = NewEngine;

	//draw window
	TextActionStats = AddControl<CTextBox>();
	TextResultStats = AddControl<CTextBox>();
	Graph_Results = AddControl<CGraph>();
}

/////////////////////////////////////////////////////////////////////////////////////
// ICom
Handle<ICom>& DebugVisual::cGetHandle()
{
	TryCreateHandle("DebugVisual");
	return IIComIO::cGetHandle();
}
void DebugVisual::cGetCommands(std::vector<Handle<ICmd> > &Commands)
{
	IIComIO::cGetCommands(Commands);
	ICom_RegisterCmd(Commands, DebugVisual, cmd_redraw, "redraw");
}
bool DebugVisual::cmd_redraw(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	// set action stats
	std::string actionText = "Action Statistics\n";
	Statistics actionStats = CurrentEngine->getActionStatistics();

	actionText += (" - 0: " + std::to_string((int)actionStats.GetNum(0)) + '\n');
	actionText += (" - 1: " + std::to_string((int)actionStats.GetNum(1)) + '\n');
	actionText += (" - 2: " + std::to_string((int)actionStats.GetNum(2)) + '\n');
	actionText += (" - 3: " + std::to_string((int)actionStats.GetNum(3)) + '\n');

	TextActionStats->Text = actionText;

	// set result stats
	std::string resultText = "Result Statistics\n";
	Statistics resultStats = CurrentEngine->getResultStatistics();

	int pos = resultStats.GetNum(Positive);
	int neg = resultStats.GetNum(Zero);

	resultText += (" - All:      " + std::to_string((int)resultStats.GetNum(all)) + '\n');
	resultText += (" - Positive: " + std::to_string(pos) + '\n');
	resultText += (" - Zero: " + std::to_string(neg) + '\n');
	resultText += (" - Ratio:    " + std::to_string((float)pos / (float)neg) + '\n');
	
	TextResultStats->Text = resultText;

	//draw graph

	std::vector<fPoint> dataPoints = resultStats.GetYGraph_Integrated();
	Graph_Results->SetDataPoints(dataPoints);

	return true;
}
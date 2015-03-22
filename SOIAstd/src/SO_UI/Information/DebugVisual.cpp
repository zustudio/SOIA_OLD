
#include "stdafx.h"
#include "SDL.h"

#include "DebugVisual.h"
#include "CTextBox.h"
#include "CGraph.h"
#include "Statistics.h"
#include "File.h"


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
	TextGeneralInfo = AddControl<CTextBox>();
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
	ICom_RegisterCmd(Commands, DebugVisual, cmd_safe, "safe");
}
bool DebugVisual::cmd_redraw(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	// set general info
	std::string text_info = "General information\n";
	text_info += " - date:        " + GetTimeAndDate() + "\n";
	text_info += " - used engine: " + CurrentEngine->getEngineName() + " (" + std::to_string(cIA_EngineVersion) + ")\n";
	text_info += " - used data:   ";
	for (std::string text_module : MDLVECTOR)
	{
		text_info += text_module + "<-";
	}
	text_info += "\n";
	TextGeneralInfo->Text = text_info;

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

bool DebugVisual::cmd_safe(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	std::string timeAndDate = GetTimeAndDate();
	std::string fileName = "../Statistics/Stats_" + timeAndDate.substr(0, 13) + "°" + timeAndDate.substr(14,2) + "'.txt";
	File f = File(fileName, FileOptions(0));
	std::string title = "----    Statistics report for SOIA    ----\n";
	f.Content.push_back(VoidPointer(title));
	f.Content.push_back(VoidPointer(TextGeneralInfo->Text));
	f.Content.push_back(VoidPointer(TextActionStats->Text));
	f.Content.push_back(VoidPointer(TextResultStats->Text));
	f.Write();
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// helpers
// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string DebugVisual::GetTimeAndDate() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d&%X", &tstruct);

	return buf;
}
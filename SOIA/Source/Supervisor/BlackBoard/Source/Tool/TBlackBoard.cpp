
#include "Definitions.h"

#include "TBlackBoard.h"
using namespace Env;
using namespace Sup;
using namespace std::chrono_literals;

////////////////////////////////////////////////////////////////////////
// ctor
TBlackBoard::TBlackBoard()
	: BaseType()
{
}
TBlackBoard::~TBlackBoard()
{
	delete Window;
}

////////////////////////////////////////////////////////////////////////
// main loop
void TBlackBoard::Main()
{
	Window = new BlackBoardWindow();
	Window->Open();

	ConfigureMainTool(Window->GetDialogue());

	while (Window->Status == EWindowStatus::Open)
	{
		std::string input;
		Dialogue->GetNextLine(input);
		ExecuteString(input);
	}
}

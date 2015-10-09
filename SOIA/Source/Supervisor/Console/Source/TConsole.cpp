
#include "Definitions.h"

#include "TConsole.h"
using namespace Supervisor;
using namespace Environment;

#include "RContainer.h"
#include "GlobalLogger.h"

#include <regex>

TConsole::TConsole()
	: BaseType(),
	bExit(false)
{
	ReflectAttributes();
}

void TConsole::Main()
{
	ConfigureMainTool(&MainDialogue);

	std::string currentTarget;
	while (!bExit && !IsStopping())
	{
		std::string input;
		Dialogue->WriteLine("");
		Dialogue->Write("> ");
		Dialogue->GetNextLine(input);
		ExecuteString(input);
	}
}

bool TConsole::cmd_exit()
{
	bExit = true;
	return true;
}

bool TConsole::cmd_echo(const std::string& InText)
{
	Dialogue->WriteLine(InText);
	return true;
}


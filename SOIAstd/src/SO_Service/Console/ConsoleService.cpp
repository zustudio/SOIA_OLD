/*
 * ConsoleService.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: mxu
 */

#include "stdafx.h"

#include "ConsoleService.h"
#include "DebugVisual.h"
#include "DataExplorer.h"


using namespace SOIA;
using namespace SO::Base;
using namespace SO::UI;
using namespace SO::Com;
using namespace IA;
using namespace std;


#include "Com_Cmd.h"

//////////////////////////////////////////////////////////////////////////////
// init

ConsoleService::ConsoleService(Engine* newEngine, ComService* NewUp) : IIComIO(NewUp)
{
	CurrentEngine = newEngine;
	ComCenter = Up;

	ComCenter->Register(cGetHandle());
	ComCenter->Register(CurrentEngine->cGetHandle());

	bLoop = true;
}

void ConsoleService::Start()
{
	std::string input = std::string("");
	std::string currentTarget = std::string("");

	while (bLoop)
	{
		std::cout << std::endl << "[User";
		if (currentTarget != "")
		{
			std::cout << "@" << currentTarget;
		}
		std::cout << "]: ";

		getline(cin, input);

		input.push_back(' ');

		std::vector<std::string> args;
		std::string newTarget = currentTarget;

		int p_Last = 0;
		for (std::string::size_type p_Char = 0; p_Char < input.size(); p_Char++)
		{
			if (input[p_Char] == ' ' || input[p_Char] == '\n')
			{
				if (input[p_Last] == '@')
				{
					newTarget = input.substr(p_Last + 1, p_Char - p_Last - 1);
				}
				else
				{
					args.push_back(input.substr(p_Last, p_Char - p_Last));
				}
				p_Last = p_Char + 1;
			}
		}

		//out vars
		std::vector<Handle<ICom> > outTargets;
		Handle<ICmd> outCmd;
		std::vector<void*> outArgs;
		bool result = false;

		//call
		result = ComCenter->TranslateString(newTarget, args, outTargets, outCmd, outArgs);

		//interpretation
		if (args.size() > 0)
		{
			if (result)
			{

				if (outTargets.size() == 1)
				{
					cSend(outTargets[0], *outCmd.getObj(), outArgs);
				}
				else
				{
					std::cout << "=> [Console]: Command ambigious.\n";
				}
			}
			else
			{
				cout << "=> [Console]: Could not parse command ( @" << newTarget << " : "<< args[0] << " )\n";
			}
		}
		else
		{
			if (result || newTarget == "")
			{
				currentTarget = newTarget;
			}
			else
			{
				std::cout << "=> [Console]: Could not find target '" << newTarget << "'.\n";
			}
		}

/*
		for (std::vector<std::string>::size_type p_Arg = 0; p_Arg < args.size(); p_Arg++)
		{
			std::string arg = args[p_Arg];

			if (arg == "exit")
				bLoop = false;
			else if (arg == "add")
			{
				if (p_Arg + 1 < args.size())
				{
					int times = std::atoi(args[p_Arg + 1].c_str());
					CurrentEngine->MThread.AddLoops(times);
					p_Arg++;
				}
				else
				{
					CurrentEngine->MThread.AddLoops(1);
				}
			}
			else if (arg == "debugvisual")
			{
				DebugVisual *visual = new DebugVisual(CurrentEngine);
				AddWindow<DebugVisual>(visual);
			}
			else if (arg == "dataexplorer")
			{
				DataExplorer* data = new DataExplorer(CurrentEngine);
				AddWindow<DataExplorer>(data);
			}
			else if (arg == "help" || arg == "?")
			{
				cout << ("");
				cout << "=> [Console]: Currently available commands are:\n    add i\n    debugvisual\n    dataexplorer\n";
			}*/
			
		//}
	}
	CurrentEngine->MThread.Disable();
}

////////////////////////////////////////////////////////////////////////////
// ICom Interface
Handle<ICom>& ConsoleService::cGetHandle()
{
	TryCreateHandle<ConsoleService>("Console"); 
	return IIComIO::cGetHandle();
}
void ConsoleService::cGetCommands(std::vector<Handle<ICmd> > &Commands)
{
	ICom_RegisterCmd(Commands, ConsoleService, cmd_echo, "echo");
	ICom_RegisterCmd(Commands, ConsoleService, cmd_create, "create");
	ICom_RegisterCmd(Commands, ConsoleService, cmd_exit, "exit");
}

bool ConsoleService::cmd_exit(const Handle<ICom> &Caller, const std::vector<void*> &Args)
{
	bLoop = false;
	return true;
}

bool ConsoleService::cmd_echo(const Handle<ICom> &Caller, const std::vector<void*> &Args)
{
	bool result = true;

	std::cout << "[" << Caller.getName() << "]: ";

	for (void* genArg : Args)
	{
		std::string* arg = (std::string*)genArg;
		if (arg)
		{
			std::cout << *arg << " ";
		}
		else
		{
			result = false;
		}
	}
	std::cout << std::endl;
	return result;
}

bool ConsoleService::cmd_create(const Handle<ICom> &Caller, const std::vector<void*> &Args)
{
	bool result = true;
	std::string* arg = (std::string*) Args[0];
	if (arg)
	{
		std::string text = *arg;
		if (text == "dataexplorer")
		{
			std::string name = std::string("dataexplorer");
			auto temp = Handle<ICom>(nullptr, name);
			ComCenter->AdjustComName(temp);

			DataExplorer* data = new DataExplorer(CurrentEngine, ComCenter);
			AddWindow<DataExplorer>(data);

			Handle<ICom> hndl = Handle<ICom>(data, name);
			ComCenter->Register(hndl, true);
		}
		else
		{
			result = false;
		}
	}
	return result;
}

/*
 * ConsoleService.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: mxu
 */

#include "stdafx.h"
#include "DebugVisual.h"
#include "Engine.h"
#include "ConsoleService.h"

using namespace SOIA;
using namespace SO::UI;
using namespace IA;
using namespace std;

//////////////////////////////////////////////////////////////////////////////
// init

ConsoleService::ConsoleService(Engine* newEngine)
{
	CurrentEngine = newEngine;
}

void ConsoleService::Start()
{
	bool bLoop = true;
	std::string input;
	while (bLoop)
	{
		getline(cin, input);
		input.push_back(' ');

		std::vector<std::string> args;

		int p_Last = 0;
		for (std::string::size_type p_Char = 0; p_Char < input.size(); p_Char++)
		{
			if (input[p_Char] == ' ' || input[p_Char] == '\n')
			{
				args.push_back(input.substr(p_Last, p_Char - p_Last));
				p_Last = p_Char + 1;
			}
		}

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
			}/*
			else if (arg == "dataexplorer")
			{
				DataExplorer^ data = gcnew DataExplorer(CurrentEngine);
				Thread^ dataThread = gcnew Thread(gcnew ThreadStart(data, &DataExplorer::Start));
				dataThread->Start();
				CurrentDataExplorers->Add(data);
			}*/
			else if (arg == "help" || arg == "?")
			{
				cout << ("");
				cout << "Currently available commands are:\n    add i\n    debugvisual\n    dataexplorer";
			}
			else
			{
				cout << "Could not parse command\n";
			}
		}
	}
	CurrentEngine->MThread.Disable();
}

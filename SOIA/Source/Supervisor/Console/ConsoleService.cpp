/*
 * ConsoleTool.cpp
 *
 *  Created on: Nov 22, 2014
 *      Author: mxu
 */

#include "Definitions.h"

// include class
#include "ConsoleService.h"
using namespace Supervisor;

// include SOIA
#include "SchroedingerApplication.h"

// include std
#include <iostream>
#include <string>


//////////////////////////////////////////////////////////////////////////////
// init

ConsoleTool::ConsoleTool(RContainer &InTools) : RApplication(InTools)
{
	// initialize variables
	bLoop = true;
	LastTalker = "";

	auto exit = Register(new RFunction<ConsoleTool>(this, &ConsoleTool::cmd_exit), "exit");
	Register(new RFunction<ConsoleTool, const std::string&>(this, &ConsoleTool::cmd_create), "create");

	// initialize Tools
	//- communication Tool
	//Srvc_Com = Up;
	//Srvc_Com->Register(cGetHandle());
	////- meaning stream Tool
	//Srvc_MeanStrm = new MeaningTool(Up);
	//Srvc_Com->Register(Srvc_MeanStrm->cGetHandle());
	////- debug Tool
	//Srvc_Debug = new DebugTool(Up);
	//Srvc_Com->Register(Srvc_Debug->cGetHandle());

	//// initialize system via Com
	//cSend("DebugSrvc", "setdebuglevel", "Draw2D", "0");
	//cSend("DebugSrvc", "setdebuglevel", "MeaningSrvc", "5");
	//cSend("DebugSrvc", "setdebuglevel", "MDebug", "2");
	//cSend("DebugSrvc", "setdebuglevel", "SOIA", "2");
	//cSend("Console", "create", "AI");
	/*cSend("SOIA", "add", "100");
	cSend("Console", "create", "debugvisual");*/

}

void ConsoleTool::Main()
{
	std::string input = std::string("");
	std::string currentTarget = std::string("");

	while (bLoop)
	{
		LastTalker = "";

		std::cout << std::endl << "[User";
		std::cout << (currentTarget == "" ? "" : "@" + currentTarget);
		std::cout << "]: ";

		std::getline(std::cin, input);

		input.push_back(' ');

		std::vector<std::string> args;
		std::string newTarget = currentTarget;

		int p_Last = 0;
		for (std::string::size_type p_Char = 0; p_Char < input.size(); p_Char++)
		{
			if (input[p_Char] == ' ' || input[p_Char] == '\n')
			{
				/*if (input[p_Last] == '@')
				{
					newTarget = input.substr(p_Last + 1, p_Char - p_Last - 1);
				}
				else
				{*/
				args.push_back(input.substr(p_Last, p_Char - p_Last));
				//}
				p_Last = p_Char + 1;
			}
		}

		bool result;
		std::vector<RTool*> OutTools;
		std::vector<RFunctionInterface*> OutFunctions;
		std::vector<Environment::VoidPointer> OutArgs;

		result = InterpretInput(args, OutTools, OutFunctions, OutArgs);

		if (result)
		{
			OutFunctions[0]->Execute(OutArgs);
		}

		
		


		////out vars
		//std::vector<Handle<ICom> > outTargets;
		//Handle<ICmd> outCmd;
		//std::vector<VoidPointer> outArgs;
		//bool result = false;

		////call
		//result = Srvc_Com->TranslateString(newTarget, args, outTargets, outCmd, outArgs);

		////interpretation
		//if (args.size() > 0)
		//{
		//	if (result)
		//	{

		//		if (outTargets.size() == 1)
		//		{
		//			cSend(outTargets[0], *outCmd.getObj(), outArgs);
		//		}
		//		else
		//		{
		//			cSend("Console", "reply", "Command ambigious. Following targets are available:");
		//			for (auto target : outTargets)
		//			{
		//				cSend("Console", "reply", " - @" + target.getName());
		//			}
		//		}
		//	}
		//	else
		//	{
		//		cout << "=> [Console]: Could not parse command ( @" << newTarget << " : "<< args[0] << " )\n";
		//	}
		//}
		//else
		//{
		//	if (result || newTarget == "")
		//	{
		//		currentTarget = newTarget;
		//	}
		//	else
		//	{
		//		std::cout << "=> [Console]: Could not find target '" << newTarget << "'.\n";
		//	}
		//}
	}
}

bool ConsoleTool::cmd_exit()
{
	std::cout << "exiting!!" << std::endl;
	return true;
}
bool ConsoleTool::cmd_create(const std::string& InName)
{
	if (InName == "schroe")
	{
		auto app = Tools->Register(new SchroedingerApplication(*Tools), "schroe");
		Tools->GetElement<RApplication>(app)->Start();
	}
	else
	{
		std::cout << "ERROR" << std::endl;
	}
	return true;
}

bool ConsoleTool::InterpretInput(const std::vector<std::string> &InInput, std::vector<RTool*> &OutTools, std::vector<RFunctionInterface*> &OutFunctions, std::vector<Environment::VoidPointer> &OutArgs)
{
	bool result = false;
	int ArgsStart = 0;

	/// Check whether target Tool name is included in input.
	if (InInput[0][0] == '@')
	{
		std::string targetToolName = InInput[0].substr(1, InInput[0].size() - 1);
		RTool* targetTool = Tools->GetElement<RTool>(targetToolName);
		if (targetTool)
		{
			OutTools.push_back(targetTool);

			if (InInput.size() > 1)
			{
				std::string targetFunctionName = InInput[1];
				RFunctionInterface* targetFunction = targetTool->GetElement<RFunctionInterface>(targetFunctionName);
				if (targetFunction)
				{
					OutFunctions.push_back(targetFunction);
					ArgsStart = 2;
					result = true;
				}
			}
		}
	}
	else
	{
		int foundFunctionsNum = 0;
		std::vector<RTool*> Tools = Tools->GetAllElements<RTool>();
		for (RTool* Tool : Tools)
		{
			RFunctionInterface* function = Tool->GetElement<RFunctionInterface>(InInput[0]);
			if (function)
			{
				OutTools.push_back(Tool);
				OutFunctions.push_back(function);
				foundFunctionsNum++;
				ArgsStart = 1;
			}
		}
		if (foundFunctionsNum == 1)
		{
			result = true;
		}
	}

	for (int i = ArgsStart; i < InInput.size(); i++)
	{
		OutArgs.push_back(InInput[i]);
	}
	return result;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
// Console Output
//bool ConsoleTool::cmd_reply(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
//{
//	//decide whether to write arrow, or blank space
//	if (Caller.getName() != LastTalker)
//	{
//		std::cout << " => ";
//	}
//	else
//	{
//		std::cout << "    ";
//	}
//	//than call echo for printing real message
//	return cmd_echo(Caller, Args);
//}
//
//bool ConsoleTool::cmd_echo(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
//{
//	bool result = true;
//
//	// do not write caller name, if last written entry is of the same origin
//	if (Caller.getName() != LastTalker)
//	{
//		std::cout << std::endl;
//		std::cout << "[" << Caller.getName() << "]: ";
//		LastTalker = Caller.getName();
//	}
//	else
//	{
//		int n = LastTalker.length();
//		for (int i = 0; i < (n+4); i++)
//		{
//			std::cout << " ";
//		}
//	}
//
//	//try to cast every passed arg to string and write it to standard console
//	for (VoidPointer genArg : Args)
//	{
//		std::string* arg = genArg.CastTo<std::string>();
//		if (arg)
//		{
//			std::cout << *arg << " ";
//		}
//		else
//		{
//			result = false;
//		}
//	}
//	std::cout << std::endl;
//	return result;
//}
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
//// Thread managment
//bool ConsoleTool::cmd_create(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
//{
//	bool result = true;
//	std::string* arg = Args[0].CastTo<std::string>();
//	if (arg)
//	{
//		std::string text = *arg;
//		SO::Thread* newThread = nullptr;
//
//		if (text == "AI")
//		{
//			cIA_Game* game = new cIA_Game();
//			CurrentEngine = new cIA_Engine(game, Srvc_Com);
//			newThread = CurrentEngine;
//		}
//		else if (text == "dataexplorer")
//		{
//			newThread = new DataExplorer(CurrentEngine, Srvc_Com, Srvc_MeanStrm);
//		}
//		else if (text == "debugvisual")
//		{
//			newThread = new DebugVisual(CurrentEngine, Srvc_Com);
//		}
//
//		if (newThread)
//		{
//			Threads.push_back(Handle<SO::Thread>(newThread, text));
//			newThread->Start();
//
//			IIComIO* newComThread = dynamic_cast<IIComIO*>(newThread);
//			if (newComThread)
//			{
//				Srvc_Com->Register(newComThread->cGetHandle());
//			}
//		}
//		else
//		{
//			result = false;
//		}
//	}
//	return result;
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// exiting
//bool ConsoleTool::cmd_exit(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
//{
//	for (auto thread : Threads)
//	{
//		thread.getObj()->Stop();
//	}
//
//	bLoop = false;
//
//	return true;
//}

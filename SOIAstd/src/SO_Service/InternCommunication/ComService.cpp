
#include "ComService.h"

using namespace SO::Base;
using namespace SO::Com;

////////////////////////////////////////////////////////////////////////////////////////
// init
ComService::ComService() //: IIComIO(this)
{
	bVerbose = false;
	Communicators = std::vector<Handle<ICom> >();
}

////////////////////////////////////////////////////////////////////////////////////////
// management
void ComService::Register(Handle<ICom> &Com, bool bForceNoNameCheck)
{
	if (!bForceNoNameCheck)
	{
		AdjustComName(Com);
	}
	//add handle to my handles
	Communicators.push_back(Com);
}
void ComService::AdjustComName(Handle<ICom> &Com)
{
	//make sure, that the current handle name is not in use
	bool bNameChanged = true;
	while (bNameChanged)
	{
		bNameChanged = false;
		for (Handle<ICom> test : Communicators)
		{
			if (test.getName() == Com.getName())
			{
				Com.IncrementName();
				bNameChanged = true;
			}
		}
	}
}

bool ComService::TranslateString(const std::string &Target, const std::vector<std::string> &Args, Handle<ICom> &outTarget, Handle<ICmd> &outCmd, std::vector<void*> &outArgs)
{
	bool result = false;

	//set target
	for (Handle<ICom> test : Communicators)
	{
		if (test.getName() == Target)
		{
			outTarget = test;
			result = true;
		}
	}

	if (!result)
	{
		return result;
	}
	else
	{
		result = false;
	}

	//set command
	ICom* com = outTarget.getObj();
	std::vector<Handle<ICmd> > commands;
	com->cGetCommands(commands);
	for (auto command : commands)
	{
		if (command.getName() == Args[0])
		{
			outCmd = command;
			result = true;
		}
	}

	if (!result)
	{
		return result;
	}

	//set arguments
	for (int i_Arg = 1; i_Arg < Args.size(); i_Arg++)
	{
		outArgs.push_back((void*) new std::string(Args[i_Arg]));
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////
// message distribution
bool ComService::Forward(const Handle<ICom> &Target, const Handle<ICom> &Caller, const ICmd &Command, const std::vector<void*> &Args)
{
	bool result = false;
	ICom* foundTarget = Target.getObj(Communicators);

	if (foundTarget)
	{
		result = Command.Execute(foundTarget, (void*)&Caller, Args);
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////
// ICom
//---- publicily executable commands ----
//bool ComService::cmd_ToggleVerbose(const std::vector<void*> &Args)
//{
//	bVerbose = !bVerbose;
//	return true;
//}
////---- implementation of neccessary overrides ----
//void ComService::cGetCommands(std::vector<Handle<ICmd> > &Commands)
//{
//	Com_Cmd<ComService>* cmd = new Com_Cmd<ComService>(&cmd_ToggleVerbose);
//	Commands.push_back(Handle<ICmd>(cmd, std::string("ToggleVerbose")));
//}

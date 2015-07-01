
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

bool ComService::TranslateString(const std::string &Target_Name, const std::vector<std::string> &Args, std::vector<Handle<ICom> > &outTargets, Handle<ICmd> &outCmd, std::vector<VoidPointer> &outArgs)
{
	bool result = false;

	//target
	Handle<ICom> Target_NameHndl = Handle<ICom>(nullptr, Target_Name);
	ICom* Target_Obj = Target_NameHndl.getObj(Communicators);
	Handle<ICom> Target_ObjHndl;

	if (Args.size() == 0)
	{
		if (Target_Obj)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	//commands
	std::vector<Handle<ICmd> > Command_Hndls = std::vector<Handle<ICmd> >();
	Handle<ICmd> Command_NameHndl = Handle<ICmd>(nullptr, Args[0]);
	Handle<ICmd> Command_ObjHndl;

	if (Target_Obj)
	{
		Target_ObjHndl = Handle<ICom>(Target_Obj, Target_Name);
		outTargets.push_back(Target_ObjHndl);

		Target_Obj->cGetCommands(Command_Hndls);
		ICmd* Cmd_Obj = Command_NameHndl.getObj(Command_Hndls);
		if (Cmd_Obj)
		{
			Command_ObjHndl = Handle<ICmd>(Cmd_Obj, Args[0]);
			result = true;
		}
	}
	else
	{
		for (auto TestTarget_ObjHndl : Communicators)
		{
			std::vector<Handle<ICmd> > TestCmd_Hndls = std::vector<Handle<ICmd> >();
			TestTarget_ObjHndl.getObj()->cGetCommands(TestCmd_Hndls);
			ICmd* Cmd_Obj = Command_NameHndl.getObj(TestCmd_Hndls);
			if (Cmd_Obj)
			{
				outTargets.push_back(TestTarget_ObjHndl);
				Command_ObjHndl = Handle<ICmd>(Cmd_Obj, Args[0]);
				result = true;
			}
		}
	}
	outCmd = Command_ObjHndl;
	

	////set target
	//for (Handle<ICom> test : Communicators)
	//{
	//	if (test.getName() == Target)
	//	{
	//		outTarget = test;
	//		result = true;
	//	}
	//}

	//if (!result)
	//{
	//	return result;
	//}
	//else
	//{
	//	result = false;
	//}

	////set command
	//ICom* com = outTarget.getObj();
	//std::vector<Handle<ICmd> > commands;
	//com->cGetCommands(commands);
	//for (auto command : commands)
	//{
	//	if (command.getName() == Args[0])
	//	{
	//		outCmd = command;
	//		result = true;
	//	}
	//}

	//if (!result)
	//{
	//	return result;
	//}

	//set arguments
	for (int i_Arg = 1; i_Arg < Args.size(); i_Arg++)
	{
		std::string* arg = new std::string(Args[i_Arg]);
		VoidPointer vp = VoidPointer(*arg);
		outArgs.push_back(vp);
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////
// message distribution
bool ComService::Forward(const Handle<ICom> &Target, const Handle<ICom> &Caller, const ICmd &Command, const std::vector<VoidPointer> &Args)
{
	bool result = false;
	ICom* foundTarget = Target.getObj(Communicators);

	if (foundTarget)
	{
		result = Command.Execute((void*)foundTarget, (void*)&Caller, Args);
	}
	return result;
}

////////////////////////////////////////////////////////////////////////////////////////
// ICom
//---- publicily executable commands ----
//bool ComService::cmd_ToggleVerbose(const std::vector<VoidPointer> &Args)
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


#include "DebugService.h"

#include <algorithm>
#include <string>

using namespace SO::Debug;

////////////////////////////////////////////////////
// init
DebugService::DebugService(ComService* NewUp) : IIComIO(NewUp)
{
	DebugVerbosities = std::vector<Handle<int> >();
}
////////////////////////////////////////////////////
// IIComIO implementation
Handle<ICom> &DebugService::cGetHandle()
{
	TryCreateHandle("DebugSrvc");
	return IIComIO::cGetHandle();
}
void DebugService::cGetCommands(std::vector<Handle<ICmd> > &Commands)
{
	IIComIO::cGetCommands(Commands);

	// user interaction
	ICom_RegisterCmd(Commands, DebugService, cmd_info, "info");
	ICom_RegisterCmd(Commands, DebugService, cmd_setdebuglevel, "setdebuglevel");

	//internal functionality
	ICom_RegisterCmd(Commands, DebugService, cmd_log, "log");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
// commands
//---- information ----
bool DebugService::cmd_info(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	cSend("Console", "reply", "There are following debug groups:");
	for (auto hndl_verbosity : DebugVerbosities)
	{
		cSend("Console", "reply", " - " + hndl_verbosity.getName() + ":\t" + std::to_string(*hndl_verbosity.getObj()));
	}
	return true;
}

bool DebugService::cmd_setdebuglevel(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	bool result = false;

	if (Args.size() >= 2)
	{
		std::string* NameOfGroup = Args[0].CastTo<std::string>();
		std::string* NewVerbosity = Args[1].CastTo<std::string>();
		if (NameOfGroup && NewVerbosity)
		{
			//get int from string
			int verbosity = std::atoi(NewVerbosity->c_str());

			// try to find importance
			Handle<int> hndl_verbosity = Handle<int>(nullptr, *NameOfGroup);
			int* p_verbosity = hndl_verbosity.getObj(DebugVerbosities);
			//else create new
			if (!p_verbosity)
			{
				p_verbosity = new int;
				hndl_verbosity = Handle<int>(p_verbosity, *NameOfGroup);
				DebugVerbosities.push_back(hndl_verbosity);
			}
			*p_verbosity = verbosity;
			result = true;
		}
	}
	return result;
}

bool DebugService::cmd_log(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	bool result = false;

	if (Args.size() >= 2)
	{
		std::string* p_str_verbosity = Args[0].CastTo<std::string>();
		std::string* p_message = Args[1].CastTo<std::string>();
		if (p_str_verbosity && p_message)
		{
			// get verbosity
			int verbosity = std::atoi(p_str_verbosity->c_str());

			// get verbosity level for caller
			int* p_allowedVerbosity = Handle<int>(nullptr, Caller.getName()).getObj(DebugVerbosities);

			if (!p_allowedVerbosity)
			{
				cSend(cGetHandle().getName(), "setdebuglevel", Caller.getName(), "5");
				p_allowedVerbosity = Handle<int>(nullptr, Caller.getName()).getObj(DebugVerbosities);
			}

			// if verbosity of current message is allowed
			if (verbosity <= *p_allowedVerbosity)
			{
				cSend("Console", "echo", *p_message);
			}
			result = true;
		}
	}

	return result;
}

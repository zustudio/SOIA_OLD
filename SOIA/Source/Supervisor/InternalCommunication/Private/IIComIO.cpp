
#include "IIComIO.h"
#include "Com_Cmd.h"
#include "Thread.h"

using namespace SO::Com;

//////////////////////////////////////////////////////////
// init
IIComIO::IIComIO(ComService* NewComService) : IIComIn(), IIComOut()
{
	Up = NewComService;
	Hndl = nullptr;
}

//////////////////////////////////////////////////////////
// public functionality
void IIComIO::cGetCommands(std::vector<Handle<ICmd> > &Commands)
{
	ICom_RegisterCmd(Commands, IIComIO, cmd_help, "help");
}
Handle<ICom>& IIComIO::cGetHandle()
{
	if (!Hndl)
	{
		TryCreateHandle("NoHandle");
	}
	return *Hndl;
}

//////////////////////////////////////////////////////////
// pre defined functions
bool IIComIO::cmd_help(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args)
{
	cSend("Console", "reply", "There are following commands available:");
	std::vector<Handle<ICmd> > commands = std::vector<Handle<ICmd> >();
	cGetCommands(commands);
	for (Handle<ICmd> command : commands)
	{
		cSend("Console", "reply", " - " + command.getName());
	}
	return true;
}


void IIComIO::TryCreateHandle(const std::string &Name)
{
	if (!Hndl)
	{
		Hndl = new Handle<ICom>(this, Name);
	}
}

//////////////////////////////////////////////////////////////
// Improvements over IIComIn & IIComOut
bool IIComIO::cSend(const Handle<ICom> &Target, const ICmd &Command, const std::vector<VoidPointer> &Args)
{
	return IIComOut::cSend(Up, Target, Command, Args);
}
bool IIComIO::cSend(const std::string &Target, const std::string &Command, const std::vector<VoidPointer> &Args)
{
	return IIComOut::cSend(Up, Target, Command, Args);
}
bool IIComIO::cSend(const std::string &Target, const std::string &Command, const std::string &Arg1, const std::string &Arg2, const std::string &Arg3, const std::string &Arg4, const std::string &Arg5)
{
	return IIComOut::cSend(Up, Target, Command, Arg1, Arg2, Arg3, Arg4, Arg5);
}
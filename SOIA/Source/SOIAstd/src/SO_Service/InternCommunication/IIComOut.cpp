
#include "IIComOut.h"

using namespace SO::Com;


/////////////////////////////////////////////////////////////////////////
// init
IIComOut::IIComOut()
{
}

/////////////////////////////////////////////////////////////////////////
// sending functionality
bool IIComOut::cSend(ComService* Up, const Handle<ICom> &Target, const ICmd &Command, const std::vector<VoidPointer> &Args)
{
	return Up->Forward(Target, cGetHandle(), Command, Args);
}
bool IIComOut::cSend(ComService* Up, const std::string &Target, const std::string &Command, const std::string &Arg1, const std::string &Arg2, const std::string &Arg3, const std::string &Arg4, const std::string &Arg5)
{
	std::vector<VoidPointer> args = std::vector<VoidPointer>();
	if (Arg1 != "")
		args.push_back(*(new std::string(Arg1)));
	if (Arg2 != "")
		args.push_back(*(new std::string(Arg2)));
	if (Arg3 != "")
		args.push_back(*(new std::string(Arg3)));
	if (Arg4 != "")
		args.push_back(*(new std::string(Arg4)));
	if (Arg5 != "")
		args.push_back(*(new std::string(Arg5)));
	return cSend(Up, Target, Command, args);

}
bool IIComOut::cSend(ComService* Up, const std::string &Target, const std::string &Command, const std::vector<VoidPointer> &Args)
{
	std::vector<std::string> CommandAndArgs = { Command };
	std::vector<Handle<ICom> > outTargets;
	Handle<ICmd> outCmd;
	std::vector<VoidPointer> outArgs;
	bool result = false;

	//call
	result = Up->TranslateString(Target, CommandAndArgs, outTargets, outCmd, outArgs);

	if (result)
	{
		return cSend(Up, outTargets[0], *outCmd.getObj(), Args);
	}
	else
	{
		return false;
	}
}
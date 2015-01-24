
#include "IIComIO.h"

using namespace SO::Com;

//////////////////////////////////////////////////////////
// init
IIComIO::IIComIO(ComService* NewComService)
{
	Up = NewComService;
}

//////////////////////////////////////////////////////////
// implementation
bool IIComIO::cSend(const Handle<ICom> &Target, const ICmd &Command, const std::vector<void*> &Args)
{
	return Up->Forward(Target, cGetHandle(), Command, Args);
}

Handle<ICom>& IIComIO::cGetHandle()
{
	if (!Hndl)
	{
		Hndl = new Handle<ICom>(this, std::string(""));
	}
	return *Hndl;
}

void IIComIO::TryCreateHandle(const std::string &Name)
{
	if (!Hndl)
	{
		Hndl = new Handle<ICom>(this, Name);
	}
}

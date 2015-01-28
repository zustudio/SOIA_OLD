
#include "IIComIO.h"

using namespace SO::Com;

//////////////////////////////////////////////////////////
// init
IIComIO::IIComIO(ComService* NewComService)
{
	Up = NewComService;
	Hndl = nullptr;
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
		TryCreateHandle<IIComIO>("");
	}
	return *Hndl;
}


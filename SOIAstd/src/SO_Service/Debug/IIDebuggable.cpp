
//super class
#ifdef def_CCCL
	#include <intrin.h>
#endif
#include <csignal>
#include <iostream>
#include <string>

#include "IIDebuggable.h"
#include "Thread.h"

using namespace SO;
using namespace SO::Debug;
using namespace SO::Com;

///////////////////////////////////////////////////////////////////
// init
IIDebuggable::IIDebuggable(ComService* NewUp) : IIComOut()
{
	init(NewUp);
}
void IIDebuggable::init(ComService* NewUp)
{
	Up = NewUp;
	hndl = nullptr;
	bEnabled = false;
}

//////////////////////////////////////////////////////////////////
// logging
void IIDebuggable::ii_Log(EDebugLevel level, const std::string &Message)
{
	if (Up)
	{
		cSend(Up, "DebugSrvc", "log", std::to_string((int)level), Message);
	}
	else
	{
		std::cout << Message << std::endl;
	}
}

//////////////////////////////////////////////////////////////////
// breaking
void IIDebuggable::ii_Break(const std::string &message)
{
	if (message != "")
	{
		ii_Log(EDebugLevel::Warning, message);
	}

	if (bEnabled)
	{
#ifdef def_CCCL
		__debugbreak();
#endif
	}
}

/////////////////////////////////////////////////////////////////////
// setters
void IIDebuggable::ii_SetBreakPointsEnabled(bool bNewEnabled)
{
	bEnabled = bNewEnabled;
}

/////////////////////////////////////////////////////////////////////
// getters
bool IIDebuggable::GetBreakEnabled()
{
	return bEnabled;
}


//super class
#include "IDebugObj.h"

//functionality
#include <intrin.h>

using namespace SO::Base;

IDebugObj::IDebugObj()
{
	bEnabled = false;
}

void IDebugObj::ii_setBreakPointsEnabled(bool bNewEnabled)
{
	bEnabled = bNewEnabled;
}

void IDebugObj::ii_break()
{
	if (bEnabled)
	{
#ifdef def_CCCL
		__debugbreak();
#endif
	}
}

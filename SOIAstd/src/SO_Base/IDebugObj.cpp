
//super class
#include "IDebugObj.h"

//functionality
#include <intrin.h>
#include <csignal>
#include <iostream>
#include <string>
#include "Thread.h"

using namespace SO;
using namespace SO::Base;

IDebugObj::IDebugObj()
{
	bEnabled = false;
	bWake = nullptr;
}

void IDebugObj::ii_SetBreakPointsEnabled(bool bNewEnabled)
{
	bEnabled = bNewEnabled;
}

void IDebugObj::ii_Break()
{
	if (bEnabled)
	{
#ifdef def_CCCL
		__debugbreak();
#endif
	}
}

void IDebugObj::ii_BreakThread(const std::string &Text)
{
	if (bEnabled)
	{
		// if class does not implement SO::Thread, simple way to reactivate thread.
		/*if (This)
		{
			std::cout << "    [BREAK]    This thread reached a breakpoint. Enter '@Target continue' to continue." << std::endl;
			BackupOfLoopsLeft = This->MThread.Loops;
			This->MThread.AddLoops(-BackupOfLoopsLeft);
		}
		else
		{*/

		std::cout << "    [BREAK]    " << Text << std::endl;
		bool b = false;
		bWake = &b;
		ii_Wait(bWake);

		//}


	}
}

void IDebugObj::ii_Continue()
{
	*bWake = true;
	ii_Wake();
}

void IDebugObj::ii_Wait(bool* bWake)
{
	std::cout << "Press a key to continue..." << std::endl;
	char i;
	i = std::getchar();
	std::cout << i;
}

void IDebugObj::ii_Wake()
{
	// IDebugObj cannot wake from break!
	// (this can be implemented in a child class)
}

/*
 * SO_Thread.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: mxu
 */

#include "Thread.h"

using namespace SO;

//////////////////////////////////////////////////////////////////////////
// init
Thread::Thread()
{
	MThread = threadConf();
}
Thread::~Thread()
{

}

///////////////////////////////////////////////////////////////////////////
void Thread::Start()
{
	while (MThread.bEnabled)
	{
		if (MThread.Loops > 0 || MThread.Loops == -1)
		{
			Tick();
			MThread.Loops = MThread.Loops > 0 ? MThread.Loops - 1 : -1;
		}
	}
}

void Thread::Tick()
{
	// do something in child class
}





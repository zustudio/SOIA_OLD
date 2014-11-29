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

}
Thread::~Thread()
{

}

///////////////////////////////////////////////////////////////////////////
void Thread::Start()
{
	while (conf.bEnabled)
	{
		if (conf.Loops > 0 || conf.Loops == -1)
		{
			Tick();
			conf.Loops--;
		}
	}
}

void Thread::Tick()
{
	// do something in child class
}





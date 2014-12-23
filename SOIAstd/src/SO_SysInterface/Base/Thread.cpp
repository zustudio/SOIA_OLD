/*
 * SO_Thread.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: mxu
 */

#include <mutex>
#include <condition_variable>

#include "Thread.h"

using namespace SO;


//////////////////////////////////////////////////////////////////////////
// struct
Thread::threadConf::threadConf()
{
	m = new std::mutex();
	cv = new std::condition_variable();
}
void Thread::threadConf::AddLoops(int n)
{
	Loops += n;
	cv->notify_one();
}
void Thread::threadConf::Disable()
{
	bEnabled = false;
	cv->notify_one();
}

//////////////////////////////////////////////////////////////////////////
// init
Thread::Thread()
{
	MThread = threadConf();
}
Thread::~Thread()
{
	delete MThread.m;
	delete MThread.cv;
}

///////////////////////////////////////////////////////////////////////////
void Thread::Start()
{
	while (MThread.bEnabled)
	{
		if (MThread.Loops > 0 || MThread.Loops == -1)
		{
			//do something
			Tick();
			MThread.Loops = MThread.Loops > 0 ? MThread.Loops - 1 : -1;
		}
		else
		{
			int* pLoops = &MThread.Loops;
			bool* pBEnabled = &MThread.bEnabled;
			//wait for wakeup
			std::unique_lock<std::mutex> lock(*MThread.m);
			MThread.cv->wait(lock, [&pLoops,&pBEnabled] {return (*pLoops) > 0 || (*pLoops) == -1 || !(*pBEnabled); });

			lock.unlock();
		}
	}
}

void Thread::Tick()
{
	// do something in child class
}





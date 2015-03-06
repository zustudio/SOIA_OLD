/*
 * SO_Thread.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: mxu
 */

#include <thread>
#include <mutex>
#include <condition_variable>

#include "Thread.h"

using namespace SO;



//////////////////////////////////////////////////////////////////////////
// public constructing / stopping
Thread::Thread()
{
	MThread = threadConf();
	MThread.m = new std::mutex();
	MThread.cv = new std::condition_variable();
}
Thread::~Thread()
{
}

void Thread::Start()
{
	MThread.bEnabled = true;
	MThread.thrd = new std::thread(&Thread::EntryPoint, this);
}
void Thread::Stop()
{
	MThread.bEnabled = false;
}

///////////////////////////////////////////////////////////////////////////
// private main loop
void Thread::EntryPoint()
{
	MThread.AddLoops(Init());

	while (MThread.bEnabled)
	{
		if (MThread.Loops > 0 || MThread.Loops == -1)
		{
			//do something
			Tick();
			MThread.Loops = MThread.Loops==0? 0 : (MThread.Loops==-1? -1 : MThread.Loops-1);
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

//////////////////////////////////////////////////////////////////////////
// struct
Thread::threadConf::threadConf()
{
	thrd = nullptr;
	m = nullptr;
	cv = nullptr;
}
Thread::threadConf::~threadConf()
{
	if (m) delete m;
	if (cv) delete cv;
	if (thrd) delete thrd;
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



/*
 * SO_Thread.cpp
 *
 *  Created on: Nov 29, 2014
 *      Author: mxu
 */

#include "Definitions.h"

//#if defined _WIN32 && defined __clang__
//#define __uncaught_exception std::uncaught_exception
//#endif
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Thread.h"
using namespace Environment;



//////////////////////////////////////////////////////////////////////////
// public constructing / stopping
Thread::Thread()
{
	ThreadStatus = EThreadStatus::AwaitingStart;

	InternalMutex = new std::mutex();
	InternalConditionVariable = new std::condition_variable();
	InternalThread = nullptr;
}
Thread::~Thread()
{
	if (InternalThread) delete InternalThread;
	if (InternalMutex) delete InternalMutex;
	if (InternalConditionVariable) delete InternalConditionVariable;
}

void Thread::Start()
{
	ThreadStatus = EThreadStatus::Working;
	InternalThread = new std::thread(&Thread::Main, this);
}
void Thread::Stop()
{
	ThreadStatus = EThreadStatus::Stopping;
}
void Thread::Join()
{
	InternalThread->join();
}

bool Thread::IsStopping()
{
	return ThreadStatus == EThreadStatus::Stopping;
}

bool Thread::IsSleeping()
{
	return ThreadStatus == EThreadStatus::Sleeping;
}

//////////////////////////////////////////////////////////////////////////
// internal
void Thread::Sleep(std::chrono::milliseconds InMS)
{
	std::this_thread::sleep_for(InMS);
}
void Thread::Sleep()
{
	ThreadStatus = EThreadStatus::Sleeping;

	EThreadStatus* p_ThreadStatus = &ThreadStatus;
	//wait for wakeup
	std::unique_lock<std::mutex> lock = std::unique_lock<std::mutex>(*InternalMutex);
	InternalConditionVariable->wait(lock, [&p_ThreadStatus] {return *p_ThreadStatus == EThreadStatus::WakingUp; });
	lock.unlock();

	ThreadStatus = EThreadStatus::Working;
}
void Thread::WakeUp()
{
	if (IsSleeping())
	{
		ThreadStatus = EThreadStatus::WakingUp;
		InternalConditionVariable->notify_one();
	}
}



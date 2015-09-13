
#pragma once

#include <chrono>

namespace std
{
	class thread;
	class mutex;
	class condition_variable;
}

namespace Environment
{
	enum class EThreadStatus
	{
		AwaitingStart,
		Working,
		Sleeping,
		WakingUp,
		Stopping
	};

	class LIBIMPEXP Thread
	{
	public:
		///////////////////////////////////////////
		// publicly starting / stopping threads
		//--- constructor ---
		Thread();
		virtual ~Thread();
		//--- to be called from thread creator ---
		void Start();
		void Stop();
		void Join();

	protected:
		///////////////////////////////////////////
		// internal workings
		//--- init ---
		virtual void Main() = 0;

	protected:
		/// Sets thread to sleeping until WakeUp call.
		void Sleep();
		void Sleep(std::chrono::milliseconds InMS);

	public:
		/// Wakes Thread.
		void WakeUp();

		/// returns true, if thread ought to be stopped.
		bool IsStopping();

		/// returns sleeping status
		bool IsSleeping();

		///////////////////////////////////////////
		// variables
	private:

		EThreadStatus ThreadStatus;

		std::thread* InternalThread;
		std::mutex* InternalMutex;
		std::condition_variable* InternalConditionVariable;
	};
}

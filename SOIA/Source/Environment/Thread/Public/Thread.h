
#pragma once

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

	protected:
		///////////////////////////////////////////
		// internal workings
		//--- init ---
		virtual void Main() = 0;

		/// Sets thread to sleeping until WakeUp call.
		void Sleep();

		/// Wakes Thread.
		void WakeUp();

		///////////////////////////////////////////
		// variables
	private:

		EThreadStatus ThreadStatus;

		std::thread* InternalThread;
		std::mutex* InternalMutex;
		std::condition_variable* InternalConditionVariable;
	};
}

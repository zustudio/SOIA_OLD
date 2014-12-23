#pragma once

namespace std
{
	class mutex;
	class condition_variable;
}

namespace SO
{
	class Thread
	{
		///////////////////////////////////////////
		// variables
	public:
		struct threadConf
		{
			//std threading
			std::mutex* m;
			std::condition_variable* cv;

			//internal threading
			//- init -
			threadConf();
			bool bEnabled = true;
			int Loops = 0;
			void Disable();
			void AddLoops(int n);
		};
	public:
		Thread::threadConf MThread;

		///////////////////////////////////////////
		//--- init ---
		Thread();
		virtual ~Thread();
		//--- main loop ---
		virtual void Start();
		//--- tick ---
		virtual void Tick();

	};
}

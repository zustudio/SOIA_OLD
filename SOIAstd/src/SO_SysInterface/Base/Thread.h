#pragma once

namespace SO
{
	class Thread
	{
		///////////////////////////////////////////
		// variables
	public:
		struct threadConf
		{
			bool bEnabled = true;
			int Loops = 0;
			void Disable() {	bEnabled = false;}
			void AddLoops(int n) { Loops += n;}
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

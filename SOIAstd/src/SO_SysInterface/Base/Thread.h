
#pragma once

//super class
#include "IDebugObj.h"

namespace std
{
	class thread;
	class mutex;
	class condition_variable;
}

namespace SO
{
	class Thread : public SO::Base::IDebugObj
	{
	public:
		///////////////////////////////////////////
		// publicly starting / stopping threads
		//--- constructor ---
		Thread();
		virtual ~Thread();
		//--- to be called from thread creator ---
		virtual void Start() final;
		virtual void Stop() final;

	private:
		///////////////////////////////////////////
		// main loop
		void EntryPoint();

		///////////////////////////////////////////
		// IDebugObj implementation
		virtual void ii_Wait(bool* bWake) override;
		virtual void ii_Wake() override;

	protected:
		///////////////////////////////////////////
		// internal workings
		//--- init ---
		virtual int Init() = 0;
		//--- tick ---
		virtual void Tick() = 0;


		///////////////////////////////////////////
		// variables
	protected:
		struct threadConf
		{
			//std threading
			std::thread* thrd;
			std::mutex* m;
			std::condition_variable* cv;

			//internal threading
			//- init -
			threadConf();
			~threadConf();
			bool bEnabled = true;
			int Loops = 0;
			void Disable();
			void AddLoops(int n);
		};
		Thread::threadConf MThread;
	};
}

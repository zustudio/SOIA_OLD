/*
 * Class IDebugObj: Can be implemented into custom classes, if those require runtime execution breaking
 */

#pragma once

#include <string>

namespace SOIA
{
	class ConsoleService;
}

namespace SO
{
	class Thread;

	namespace Base
	{
		class IDebugObj
		{
			friend class SOIA::ConsoleService;

		public:
			////////////////////////////////////////////////////////////
			// functions
			//---- init ----
			IDebugObj();
			//---- activate break points ----
			void ii_SetBreakPointsEnabled(bool bNewEnabled);
			//---- to be called by child class, at breakable code ----
			void ii_Break();
			void ii_BreakThread(const std::string &Text = "");
			void ii_Continue();
		protected:
			//---- to be overriden by child classes, if custom wait procedures are required ----
			virtual void ii_Wait(bool* bWake);
			virtual void ii_Wake();
			////////////////////////////////////////////////////////////
			// variables
		private:
			//---- activation state ----
			bool bEnabled;
			//---- continue-information ----
			bool* bWake;
		};
	}
}
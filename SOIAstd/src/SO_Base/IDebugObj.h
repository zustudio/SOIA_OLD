/*
 * Class IDebugObj: Can be implemented into custom classes, if those require runtime execution breaking
 */

#pragma once

namespace SO
{
	namespace Base
	{
		class IDebugObj
		{
		public:
			////////////////////////////////////////////////////////////
			// functions
			//---- init ----
			IDebugObj();
			//---- activate break points ----
			void ii_setBreakPointsEnabled(bool bNewEnabled);
		protected:
			//---- to be called by child class, at breakable code ----
			void ii_break();
			////////////////////////////////////////////////////////////
			// variables
		private:
			//---- activation state ----
			bool bEnabled;
		};
	}
}
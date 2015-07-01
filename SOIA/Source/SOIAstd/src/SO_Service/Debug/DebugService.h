
#pragma once

//Super class
#include "IIComIO.h"

//using directives
using namespace SO::Com;

namespace SO
{
	namespace Debug
	{
		class DebugService : public IIComIO
		{
		public:
			//////////////////////////////////////////////
			// functions
			//---- init ----
			DebugService(ComService* Up);
			//---- IIComIO implementation ----
			virtual Handle<ICom> &cGetHandle() override;
			virtual void cGetCommands(std::vector<Handle<ICmd> > &Commands) override;
			// user interaction
			T_com_cmd_func cmd_info;
			T_com_cmd_func cmd_setdebuglevel;
			// internal functionality
			T_com_cmd_func cmd_log;

		private:
			//////////////////////////////////////////////
			// vars
			std::vector<Handle<int> > DebugVerbosities;
		};
	}
}

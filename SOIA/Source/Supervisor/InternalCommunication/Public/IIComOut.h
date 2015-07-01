
#pragma once

//Super
#include "ICom.h"

#include "ComService.h"

namespace SO
{
	namespace Com
	{
		class IIComOut : public virtual ICom
		{
		public:
			//////////////////////////////////////////////////
			// functions
			//---- init ----
			IIComOut();
		protected:
			//---- implementation of sending functionality for child classes ----
			virtual bool cSend(ComService* Up, const Handle<ICom> &Target, const ICmd &Command, const std::vector<VoidPointer> &Args);
			virtual bool cSend(ComService* Up, const std::string &Target, const std::string &Command, const std::vector<VoidPointer> &Args);
			virtual bool cSend(ComService* Up, const std::string &Target, const std::string &Command, const std::string &Arg1 = "", const std::string &Arg2 = "", const std::string &Arg3 = "", const std::string &Arg4 = "", const std::string &Arg5 = "");

		};
	}
}
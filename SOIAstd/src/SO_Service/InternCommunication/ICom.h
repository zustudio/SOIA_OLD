
#pragma once

#include "ICmd.h"
#include "Handle.h"

namespace SO
{
	namespace Com
	{
		class ICom
		{
		public:
			/////////////////////////////////
			// getting information
			virtual void cGetCommands(std::vector<SO::Base::Handle<SO::Base::ICmd> > &Commands) = 0;

			////////////////////////////////
			// io
			virtual bool cSend(const SO::Base::Handle<SO::Com::ICom> &Target, const SO::Base::ICmd &Command, const std::vector<SO::Base::VoidPointer> &Args) = 0;
			/*virtual void cReceive(const ICom &caller, const Com_Cmd &Cmd) = 0;*/
		};
	}
}

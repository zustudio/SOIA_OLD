
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
			// Common Input / Output information
			virtual SO::Base::Handle<ICom>& cGetHandle() = 0;

			/////////////////////////////////
			// Rather input information - refactor into IIComIn?
			virtual void cGetCommands(std::vector<SO::Base::Handle<SO::Base::ICmd> > &Commands) = 0;
		};
	}
}

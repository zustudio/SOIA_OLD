
#pragma once

#include "ExData.h"
#include "ExGroup.h"
#include "ExDSet.h"

#include "ICom.h"
#include "Com_Cmd.h"

#include <deque>

#include "../../SO_Base/Handle.h"

using namespace IA::MeaningStream;
using namespace SO::Base;
using namespace SO::Com;

namespace SO
{
	namespace MeaningStream
	{
		class MeaningService : ICom
		{
		public:
			//////////////////////////////////////////////////////
			// external callable commands
			bool cmd_CreateDSet(const Handle<ICom> &Caller, const std::vector<void*> &Args);
			void cmd_AddDGroup(const Handle<ICom> &Caller, const std::vector<void*> &Args);

			//////////////////////////////////////////////////////
			// management
			MeaningService();
			~MeaningService();

			//////////////////////////////////////////////////////
			// vars
			std::vector<Handle<ExDSet>> DataSets;

			//////////////////////////////////////////////////////
			// ICom interface
//			virtual void cReceive(const ICom &caller, const Com_Cmd &Cmd) override;
		};
	}
}

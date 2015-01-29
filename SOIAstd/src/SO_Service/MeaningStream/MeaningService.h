
#pragma once

#include "ExData.h"
#include "ExGroup.h"
#include "ExDSet.h"

#include "IIComIO.h"
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
		class MeaningService : public IIComIO
		{
		public:
			//////////////////////////////////////////////////////
			// management
			MeaningService(ComService* Up);
			~MeaningService();

			//////////////////////////////////////////////////////
			// vars
			std::vector<Handle<ExDSet>> DataSets;

			//////////////////////////////////////////////////////
			// ICom
			//---- inteface ----
			void cGetCommands(std::vector<Handle<ICmd> > &Commands) override;
			Handle<ICom>& cGetHandle() override;
			//---- external callable commands ----
			T_com_cmd_func cmd_create;

		};
	}
}

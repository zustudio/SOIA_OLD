
#pragma once

//parent class
#include "IIComIO.h"
//implementation neccessities
#include "Com_Cmd.h"

//properties
#include "IData.h"
#include "ExData.h"
#include "ExGroup.h"
#include "ExDSet.h"
#include "Handle.h"

#include <deque>

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
			// public access
			Handle<ExDSet> GetSetByName(const std::string &Name);

			//////////////////////////////////////////////////////
			// ICom
			//---- inteface ----
			void cGetCommands(std::vector<Handle<ICmd> > &Commands) override;
			Handle<ICom>& cGetHandle() override;
			//---- external callable commands ----
			T_com_cmd_func cmd_info;
			T_com_cmd_func cmd_addgroup;
			T_com_cmd_func cmd_addgroupstrings;
			T_com_cmd_func cmd_interpretdata;
			T_com_cmd_func cmd_convertdata;
			T_com_cmd_func cmd_adddata;

			/////////////////////////////////////////////////////
			// FUNCTIONALITY
			//---- data conversion ----
			ExData* Convert(IA::IData* myData, int Depth);
			ExData* exe_Convert(IA::IData* Current, int Depth, std::deque<IA::IData*>* Ignore);
			ExData* getConverted(IA::IData* data);
			//---- data parentage interpretation ----
			void SetHierarchicBonds(ExData* Current);
			void exe_SetHierarchicDistances(ExData* Current, ExData* Caller, int Distance);
			void CreateAutoGroups();

			//////////////////////////////////////////////////////
			// vars
			std::vector<Handle<ExDSet>> DataSets;
			std::deque<ExData*> RegisteredData;
		private:
			IA::Engine* CurrentEngine;
		};
	}
}

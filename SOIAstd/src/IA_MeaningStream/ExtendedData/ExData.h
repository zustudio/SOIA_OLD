
#pragma once
#include "IA_SSt.h"
#include "stdafx.h"
#include "MTypes.h"

using namespace IA::Def_MTypes;

namespace IA
{
	namespace MeaningStream
	{
		class ExData
		{
		public:
			///////////////////////////////////////////////////
			// vars
			IData* CurrentSource;
			std::deque<ExData*>* CurrentAllObjects;

			int HierarchicDistance;
			ExData* Parent;
			std::deque<ExData*> Children;
			fPoint Location;
			fPoint Extend;

			///////////////////////////////////////////////////
			// functions
			//---- init ----
			ExData(IData* NewSource, std::deque<ExData*> *AllObjects);
			//---- properites ----
			std::string* getText();
			//---- network mirroring ----
			std::deque<ExData*>* getConnected(LinkType ConnectionType = LinkType::Both);
		};
	}
}

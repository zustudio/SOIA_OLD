
#pragma once

#include "stdafx.h"

#include "VectorND.h"
//#include "fPoint.h"
//#include "IData.h"
//	#include "MTypes.h"


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

			struct SInterpretedProps
			{
				VectorND<float> IntExtend = VectorND<float>(0);
			};
			SInterpretedProps InterpProps;

			///////////////////////////////////////////////////
			// functions
			//---- init ----
			ExData(IData* NewSource, std::deque<ExData*> *AllObjects);
			//---- properites ----
			std::string* getText();
			//---- network mirroring ----
			std::deque<ExData*>* getConnected(LinkType ConnectionType = LinkType::T_NormLink | LinkType::Downlink | LinkType::Uplink);
		};
	}
}

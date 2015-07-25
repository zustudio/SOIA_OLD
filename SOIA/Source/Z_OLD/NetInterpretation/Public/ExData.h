
#pragma once


#include "fCanvasObject.h"
#include "VectorND.h"
//#include "fPoint.h"
//#include "IData.h"
//	#include "MTypes.h"


namespace IA
{
	namespace MeaningStream
	{
		class ExData : public Graphics::fCanvasObject
		{
		public:

			///////////////////////////////////////////////////
			// functions
			//---- init ----
			ExData(IData* NewSource, std::deque<ExData*> *AllObjects);
			//---- properites ----
			std::string* getText();
			//---- network mirroring ----
			std::deque<ExData*>* getConnected(LinkType ConnectionType = LinkType::T_NormLink | LinkType::Downlink | LinkType::Uplink);
			//---- fCanvasObject implementation ----
			virtual std::vector<fCanvasObject*>* GetCustomParts() override;
			virtual void Highlight(bool bEnable);

			///////////////////////////////////////////////////
			// structs
			struct SInterpretedProps
			{
				VectorND<float> IntExtend = VectorND<float>(0);
				VectorND<float> IntLocation = VectorND<float>(0);
				VectorND<float> FloatExtend = VectorND<float>(0);
				VectorND<float> FloatLocation = VectorND<float>(0);
			};

			///////////////////////////////////////////////////
			// vars
			//---- idata ----
			IData* CurrentSource;
			//---- exdata ----
			std::deque<ExData*>* CurrentAllObjects;

			//---- properties ----
			int HierarchicDistance;
			ExData* Parent;
			std::deque<ExData*> Children;
			fPoint Location;
			fPoint Extend;
			SInterpretedProps InterpProps;
			bool bHighlighted;
		};
	}
}

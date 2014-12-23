// c Maxim Urschumzew 2014

#pragma once

#include "CCanvas.h"
#include "ExData.h"

using namespace IA;
using namespace IA::MeaningStream;


namespace SO
{
	class DEGraph : public CCanvas
	{
	public:
		//////////////////////////////////////////////////////
		// vars
		//---- instances ----
		std::deque<ExData*> AllDrawnObjects;
		Data* CurrentData;

		//////////////////////////////////////////////////////
		// functions
		//---- init ----
		DEGraph(Data* DataToDraw, Window_Base* newWindow = nullptr, const fPoint &newLoc = fPoint(), const fPoint &newSize = fPoint());
		//---- draw ----
		virtual void Draw() override;
		void Draw(int Depth);

		//---- converting ----
		ExData* Convert(Data* Data, int Depth);
		ExData* exe_Convert(Data* Current, int Depth, std::deque<Data*>* Ignore);
		void SetHierarchicBonds(ExData* Current);
		void exe_SetHierarchicDistances(ExData* Current, ExData* Caller, int Distance);
		int LongestHorizontalDataLine(ExData* Parent);
		int exe_LongestHorizontalDataLine(ExData* Current);
		int HorizontalDataLine(ExData* Parent, int Distance);
		void SetObjectPosition(ExData* Parent, int Depth);
		void exe_SetObjectPosition(ExData* Parent, ExData* Current, int TotalDepth, fPoint &CurrentLoc);
		std::deque<ExData*>* GetObjectsWithDistance(int Distance);
		void DrawObjects();
		void DrawConnections();
	};
}

#pragma once

#include "Window.h"
#include "IIComIO.h"

namespace IA
{
	class Engine;
}

namespace SO
{
	namespace Drawing
	{
		class CTextBox;
		class CGraph;
	}

	namespace UI
	{
		class DebugVisual : public Window, public SO::Com::IIComIO
		{
		public:
			///////////////////////////////////////////////////////////
			// functions
			//---- init ----
			DebugVisual(IA::Engine* NewEngine, SO::Com::ComService* NewUp);
			//---- icom ----
			virtual void cGetCommands(std::vector<Handle<ICmd> > &Commands) override;
			virtual Handle<ICom> &cGetHandle() override;
			T_com_cmd_func cmd_redraw;
			T_com_cmd_func cmd_safe;
			//---- helpers ----
			const std::string GetTimeAndDate();

		private:
			///////////////////////////////////////////////////////////
			// controls
			SO::Drawing::CTextBox* TextGeneralInfo;
			SO::Drawing::CTextBox* TextActionStats;
			SO::Drawing::CTextBox* TextResultStats;
			Drawing::CGraph* Graph_Results;

			///////////////////////////////////////////////////////////
			// data
			IA::Engine* CurrentEngine;
		};
	}
}
#pragma once

#include "Window.h"
#include "IIComIO.h"

#include "IDraw.h"
#include "CCanvas.h"
#include "CTextBox.h"
#include "MeaningService.h"

namespace IA
{
	class Engine;
}

namespace SO
{
	namespace Drawing
	{
		class DEGraph;
	}

	namespace UI
	{
		class DataExplorer : public Window, public SO::Com::IIComIO
		{
		public:
			///////////////////////////////////////////////////////////
			// functions
			DataExplorer(IA::Engine* NewEngine, SO::Com::ComService* NewUp, SO::MeaningStream::MeaningService* MSrvc);
			virtual void Tick() override;
			//---- ICom -----
			virtual void cGetCommands(std::vector<Handle<ICmd> > &Commands) override;
			virtual Handle<ICom>& cGetHandle() override;
			//---- commands ----
			T_com_cmd_func cmd_redraw;
			T_com_cmd_func cmd_setset;
			T_com_cmd_func cmd_select;
			T_com_cmd_func cmd_deselect;

		private:
			///////////////////////////////////////////////////////////
			// settings
			//---- data access point ----
			IA::Engine* CurrentEngine; // not needed?
			SO::MeaningStream::MeaningService* MeaningSrvc;
			//---- drawn set handle ----
			std::string DrawnSet;
			ExData* SelectedData;

			///////////////////////////////////////////////////////////
			// controls
			SO::Drawing::CTextBox* TopTextBox;
			SO::Drawing::CTextBox* TextBox_SelectedDataInfo;
			SO::Drawing::CCanvas* Canvas;
			IDraw* Drawable;
		};
	}
}
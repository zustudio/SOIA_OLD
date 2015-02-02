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

		private:
			///////////////////////////////////////////////////////////
			// data
			IA::Engine* CurrentEngine;

			///////////////////////////////////////////////////////////
			// controls
			//DEGraph* myDEGraph;
			SO::Drawing::CTextBox* TopTextBox;
			SO::Drawing::CCanvas* Canvas;
			IDraw* Drawable;

			//////////////////////////////////////////////////////////
			// Service
			SO::MeaningStream::MeaningService* MeaningSrvc;
		};
	}
}
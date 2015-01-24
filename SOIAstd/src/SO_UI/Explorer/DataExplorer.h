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
		class DEGraph;
	}

	namespace UI
	{
		class DataExplorer : public Window, public SO::Com::IIComIO
		{
		public:
			///////////////////////////////////////////////////////////
			// functions
			DataExplorer(IA::Engine* NewEngine, SO::Com::ComService* NewUp);
			virtual void Start() override;
			//---- ICom -----
			virtual void cGetCommands(std::vector<Handle<ICmd> > &Commands) override;

		private:
			///////////////////////////////////////////////////////////
			// data
			IA::Engine* CurrentEngine;

			///////////////////////////////////////////////////////////
			// controls
			DEGraph* myDEGraph;
		};
	}
}
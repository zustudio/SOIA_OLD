#pragma once

#include "Window.h"

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
		class DataExplorer : public Window
		{
		public:
			///////////////////////////////////////////////////////////
			// data
			IA::Engine* CurrentEngine;

			///////////////////////////////////////////////////////////
			// controls
			DEGraph* myDEGraph;

			///////////////////////////////////////////////////////////
			// functions
			DataExplorer(IA::Engine* NewEngine);
			virtual void Start() override;
		};
	}
}
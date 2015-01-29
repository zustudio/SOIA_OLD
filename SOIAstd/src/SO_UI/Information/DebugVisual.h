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
		class CTextBox;
	}

	namespace UI
	{
		class DebugVisual : public Window
		{
		public:
			///////////////////////////////////////////////////////////
			// data
			IA::Engine* CurrentEngine;

			///////////////////////////////////////////////////////////
			// controls
			SO::Drawing::CTextBox* TextMain;

			///////////////////////////////////////////////////////////
			// functions
			DebugVisual(IA::Engine* NewEngine);
		};
	}
}
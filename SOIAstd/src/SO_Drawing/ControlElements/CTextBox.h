#pragma once

#include "Control.h"
#include <string>
#include <deque>

namespace SO
{
	namespace Drawing
	{
		class fPoint;

		class CTextBox : public Control
		{
		public:
			//////////////////////////////////////////////////////////
			// vars
			std::deque<std::string*> Texts;
			std::string Text;
			//////////////////////////////////////////////////////////
			// functions
			//---- init ----
			CTextBox(Window_Base* newWindow = nullptr, const fPoint &newLoc = fPoint(), const fPoint &newSize = fPoint());
			//---- draw ----
			virtual void Draw() override;
			//---- text ----
			void ProcessText();
		};
	}
}
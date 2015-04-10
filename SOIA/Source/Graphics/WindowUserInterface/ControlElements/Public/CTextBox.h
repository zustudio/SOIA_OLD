#pragma once

#include "Control.h"
#include <string>
#include <deque>

namespace SO
{
	namespace Drawing
	{
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
			CTextBox(Window_Base* newWindow = nullptr, const cPoint &newLoc = cPoint(), const cPoint &newSize = cPoint());
			//---- draw ----
			virtual void Draw() override;
			//---- text ----
			void ProcessText();
		};
	}
}
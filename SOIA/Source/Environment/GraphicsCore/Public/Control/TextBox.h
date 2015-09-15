
#pragma once

#include "GraphicsControl.h"

#include "TextObject.h"
#include "TextCursor.h"

#include <chrono>

namespace Environment
{
	enum class ETextBoxMode
	{
		Editable,
		NotEditable
	};

	class LIBIMPEXP TextBox : public GraphicsControl
	{
	public:
		TextBox(MBoundaries* InBoundaries, pxMargins InMargins, ETextBoxMode InMode = ETextBoxMode::NotEditable);

		virtual void Update() override;

		std::vector<pxPoint> CalculateCursorLocation();
		Vector2D<int> CursorPos_1DTo2D(int InPosition);
		int CursorPos_2DTo1D(Vector2D<int> const & InPosition);

		void SetText(std::string const & InText);

		virtual void Event_CharacterEntered(unsigned int InChar) override;
		virtual void Event_KeyChanged(EventInfo_KeyChanged const & InInfo) override;

	private:
		std::string Text;
		std::vector<TextObject> TextObjects;
		ETextBoxMode Mode;

		// cursor
		TextCursor Cursor;
	};
}

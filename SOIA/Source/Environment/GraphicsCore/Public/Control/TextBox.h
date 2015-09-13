
#pragma once

#include "GraphicsControl.h"

#include "TextObject.h"

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
		virtual ~TextBox();

		virtual void Update() override;
		void UpdateCursor();

		void RequestCursorUpdate();

		void SetText(std::string const & InText);

		virtual void Event_CharacterEntered(unsigned int InChar) override;
		virtual void Event_KeyChanged(EventInfo_KeyChanged const & InInfo) override;

	private:
		int GetCurserPositionInText();

	private:
		std::string Text;
		std::vector<TextObject> TextObjects;
		ETextBoxMode Mode;

		// cursor
		GeometryObject* Cursor;
		Vector2D<int> CursorPosition;
		std::chrono::steady_clock::time_point LastCursorBlink;
		bool bCursorOn;
	};
}

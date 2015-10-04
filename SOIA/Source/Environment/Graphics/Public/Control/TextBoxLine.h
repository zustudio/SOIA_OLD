
#pragma once

#include "Definitions.h"

#include "TextObject.h"

#include "FontTexture2D.h"

namespace Environment
{
	class TextBoxLine : public TextObject
	{
	public:
		TextBoxLine(MBoundaries* InBoundaries, pxMargin & InOutTop, FontTexture2D* InFontTexture);

		void Fill(ContainerAwareIteratorSet<std::string> & InOutWholeTextIterators);

	private:
		std::string PeekWord(ContainerAwareIteratorSet<std::string> const & InWholeTextIterators);
		static bool IsWordTerminator(char InChar);
		static bool IsSpaceCharacter(char InChar);

	public:
		std::string CurrentText;
	private:
		FontTexture2D* FontTexture;
	};
}

#pragma once

#include "Definitions.h"

#include "FontTexture2D.h"

namespace Environment
{
	class TextBoxLine
	{
	public:
		TextBoxLine(FontTexture2D* InFontTexture, int InMaxWidth);
		void Fill(ContainerAwareIteratorSet<std::string> & InOutWholeTextIterators);
	private:
		std::string PeekWord(ContainerAwareIteratorSet<std::string> const & InWholeTextIterators);
		static bool IsWordTerminator(char InChar);
		static bool IsSpaceCharacter(char InChar);

	public:
		std::string CurrentText;
	private:
		FontTexture2D* FontTexture;
		int MaxWidth;
	};
}
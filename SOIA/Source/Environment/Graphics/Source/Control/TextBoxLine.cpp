
#include "Definitions.h"

#include "TextBoxLine.h"
using namespace Environment;

TextBoxLine::TextBoxLine(MBoundaries* InBoundaries, pxMargin & InOutTop, FontTexture2D * InFontTexture)
	: TextObject(InBoundaries, pxMargins(2, InOutTop, 2, -1 * InFontTexture->GetSpriteSize().Y), ""),
	FontTexture(InFontTexture)
{
	InOutTop = pxMargin(int(InOutTop) + InFontTexture->GetSpriteSize().Y);
}

void TextBoxLine::Fill(ContainerAwareIteratorSet<std::string> & InOutWholeTextIterators)
{
	auto iter_start = InOutWholeTextIterators.Current;
	int currentTextWidth = 0;	// in pixels
	while (InOutWholeTextIterators.Current != InOutWholeTextIterators.End)
	{
		std::string word = PeekWord(InOutWholeTextIterators);
		int wordWidth = FontTexture->CalculateTextWidth(word);

		currentTextWidth += wordWidth;
		if (currentTextWidth > GetSize().Width)
		{
			break;
		}
		InOutWholeTextIterators.Current += word.size();
		if ((*--word.end()) == '\n')
		{
			break;
		}
	}
	auto iter_end = InOutWholeTextIterators.Current;

	SetText(std::string(iter_start, iter_end));
}

std::string TextBoxLine::PeekWord(ContainerAwareIteratorSet<std::string> const & InWholeTextIterators)
{
	std::string word;
	auto iter_char = InWholeTextIterators.Current;

	do
	{
		word.push_back(*iter_char);
	} while (!IsWordTerminator(*iter_char) && ++iter_char != InWholeTextIterators.End);
	
	return word;
}

bool TextBoxLine::IsWordTerminator(char InChar)
{
	return IsSpaceCharacter(InChar)
		|| InChar == '.'
		|| InChar == ','
		|| InChar == ';';
}

bool TextBoxLine::IsSpaceCharacter(char InChar)
{
	return InChar == ' '
		|| InChar == '\n'
		|| InChar == '\t';
}


#include "Definitions.h"

#include "TextBoxLine.h"
using namespace Environment;

TextBoxLine::TextBoxLine(FontTexture2D * InFontTexture, int InMaxWidth)
	:
	FontTexture(InFontTexture),
	MaxWidth(InMaxWidth),
	CurrentText("")
{}

void TextBoxLine::Fill(ContainerAwareIteratorSet<std::string> & InOutWholeTextIterators)
{
	int currentTextWidth = 0;	// in pixels
	while (InOutWholeTextIterators.Current != InOutWholeTextIterators.End)
	{
		std::string word = PeekWord(InOutWholeTextIterators);
		int wordWidth = FontTexture->CalculateTextWidth(word);

		currentTextWidth += wordWidth;
		if (currentTextWidth > MaxWidth)
		{
			break;
		}
		CurrentText += word;
		InOutWholeTextIterators.Current += word.size();
		if ((*--word.end()) == '\n')
		{
			break;
		}
	}
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

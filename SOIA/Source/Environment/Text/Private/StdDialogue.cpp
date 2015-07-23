
#include "Definitions.h"

#include "StdDialogue.h"
using namespace Environment;

#include <iostream>
#include <conio.h>

void StdDialogue::Write(const std::string& InText)
{
	std::cout << InText;
}

void StdDialogue::WriteLine(const std::string& InText)
{
	std::cout << InText << std::endl;
}

void StdDialogue::GetNextLine(std::string& OutText)
{
	OutText = "";
	char prev;
	char ch;
	while ((ch = _getch()) != 13)
	{
		if (ch == '\t')
		{
			if (prev == ch)
			{
				std::cout << "DoubleTab";
				prev = 0;
			}
			else
			{
				std::cout << "Tab";
			}
		}
		else
		{
			if (ch == '\b')
			{
				_putch(ch);
				_putch(' ');
				_putch(ch);
				OutText = OutText.substr(0, OutText.size() - 1);
			}
			else
			{
				_putch(ch);
				OutText += ch;
			}
		}
		prev = ch;
	}
	_putch('\n');
}
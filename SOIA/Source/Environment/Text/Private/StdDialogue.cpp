
#include "Definitions.h"

#include "StdDialogue.h"
using namespace Environment;

#include <iostream>

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
	std::getline(std::cin, OutText);
}

#include "Definitions.h"

#include "ElementFile.h"
using namespace Environment;

////////////////////////////////////////////////////////////////
// Init
ElementFile::ElementFile(Path const & InPath)
	: IOFile(InPath)
{

}

////////////////////////////////////////////////////////////////
// Writing
void Environment::ElementFile::WriteMultiple(std::vector<RElement*> InElements, EElementSelectionMode InSelectionMode)
{
	for (RElement* element : InElements)
	{
		WriteSingle(element, InSelectionMode);
	}
}

void Environment::ElementFile::WriteSingle(RElement * InElement, EElementSelectionMode InSelectionMode)
{

}



////////////////////////////////////////////////////////////////
// Reading
std::vector<RElement*> Environment::ElementFile::ReadMultiple(int InCount)
{
	std::vector<RElement*> elements = std::vector<RElement*>(InCount);
	RElement* element = nullptr;

	element = ReadSingle();
	while (element && InCount--)
	{
		elements.push_back(element);
		element = ReadSingle();
	}

	return elements;
}

RElement * Environment::ElementFile::ReadSingle()
{
	return nullptr;
}

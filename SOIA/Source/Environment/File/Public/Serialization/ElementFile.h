
#pragma once

#include "IOFile.h"

#include "RElement.h"

namespace Environment
{
	enum class EElementSelectionMode : int
	{
		Single,
		Recursive
	};

	class ElementFile : public IOFile
	{
	public:
		////////////////////////////////////////////////////////////////
		// Functions

		//----- init -----
		ElementFile(Path const& InPath);

		//----- Writing to file -----
		void WriteSingle(RElement* InElement, EElementSelectionMode InSelectionMode);
		void WriteMultiple(std::vector<RElement*> InElements, EElementSelectionMode InSelectionMode);

		//----- Reading from file -----
		RElement* ReadSingle();
		std::vector<RElement*> ReadMultiple(int InCount);
	};
}

#pragma once

#include "IOFile.h"

#include "RElement.h"
#include "Tokenizer.h"

namespace Environment
{
	enum class EElementSelectionMode : int
	{
		Single,
		Recursive
	};

	class LIBIMPEXP ElementFile : public IOFile
	{
		////////////////////////////////////////////////////////////////
		// Functions
	public:
		//----- init -----
		ElementFile(Path const& InPath);

		//----- Writing to file -----
		void WriteSingle(RElement* InElement, EElementSelectionMode InSelectionMode);
		void WriteMultiple(std::vector<RElement*> InElements, EElementSelectionMode InSelectionMode);

		//----- Reading from file -----
		RElement* ReadSingle();
		std::vector<RElement*> ReadMultiple(int InCount);

		////////////////////////////////////////////////////////////////
		// Variables
	private:
		//----- tokenization -----
		Tokenizer ElementTokenizer;
	};
}
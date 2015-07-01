
#pragma once

#include "EquationTokens.h"
#include "MathContainer.h"
#include "D1D1GenericFunction.h"

#include <string>
#include <vector>

namespace Environment
{
	class LIBIMPEXP EquationString
	{
		////////////////////////////////////////////////////////////////
		// Enumerations
		enum class ECharacterType
		{
			WhiteSpace,
			Letter,
			Number,
			Operator,
			ComparisonSign,
			Bracket,
			Comma
		};

		////////////////////////////////////////////////////////////////
		// Functions
	public:
		explicit EquationString(const std::string& InString);

		D1D1GenericFunction Parse(MathContainer&);

		EquationTokens Tokenize();

	private:
		//----- generating tokens -----
		void DivideIntoFormalParts();
		
		//----- helper functions -----
		ECharacterType GetCharacterType(const char&);

		////////////////////////////////////////////////////////////////
		// Variables
		std::string String;
		std::vector<std::string> FormalParts;

		
	};
}
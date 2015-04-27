
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/EquationString.h"
using namespace Environment;


#include <iostream>

EquationString::EquationString(const std::string& InString)
{
	String = InString + ' ';
}

void EquationString::Parse(MathContainer& InRuntime)
{
	EquationTokens tokens = Tokenize();
	EquationToken* mainToken = tokens.GenerateOperandDependency();
	if (mainToken)
	{
		mainToken->rec_RegisterToken(&InRuntime);
	}
	else
	{
		std::cout << "String could not be resolved to a single main token." << std::endl;
	}
}

EquationTokens EquationString::Tokenize()
{
	DivideIntoFormalParts();
	return EquationTokens(FormalParts);
}

//////////////////////////////////////////////////////////////
// Private Calculation
void EquationString::DivideIntoFormalParts()
{
	FormalParts.clear();

	auto startOfCurrentPart = String.begin();

	for (auto iter = String.begin(); iter != String.end(); iter++)
	{
		if (GetCharacterType(*iter) != GetCharacterType(*startOfCurrentPart))
		{
			FormalParts.push_back(std::string(startOfCurrentPart, iter));
			startOfCurrentPart = iter;
		}
	}
}

//////////////////////////////////////////////////////////////
// Helper Functions
EquationString::ECharacterType EquationString::GetCharacterType(const char& InChar)
{
	ECharacterType result;

	if (InChar == ' ')
		result = ECharacterType::WhiteSpace;
	else if (InChar == '(' || InChar == ')')
		result = ECharacterType::Bracket;
	else if (InChar == '+' || InChar == '-' || InChar == '*' || InChar == '/')
		result = ECharacterType::Operator;
	else if (InChar == '=' || InChar == '>' || InChar == '<')
		result = ECharacterType::ComparisonSign;
	else if (InChar == ',')
		result = ECharacterType::Comma;
	else if (InChar >= 'a' && InChar <= 'z' || InChar >= 'A' && InChar <= 'Z' || InChar == '_')
		result = ECharacterType::Letter;
	else if (InChar >= '1' && InChar <= '9' || InChar == '0' || InChar == '.')
		result = ECharacterType::Number;
	else
		std::cout << "[EquationString]: ERROR: could not identify character (" << InChar << ")\n";
	return result;
}
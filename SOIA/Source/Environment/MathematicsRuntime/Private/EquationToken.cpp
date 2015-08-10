
#include "Definitions.h"

#include "EquationToken.h"
using namespace Environment;

#include "OP_Add.h"
#include "OP_Substract.h"
#include "OP_Multiply.h"
#include "OP_Divide.h"
#include "OP_Select.h"
#include "OP_GreaterThan.h"
#include "OP_CalculateFunction.h"
#include "Constant.h"
#include "Variable.h"

#include <iostream>

EquationToken::EquationToken(const std::string& InString)
	:
	String(InString)
{

	if (InString[0] == ' ')
		Type = TokenType::WhiteSpace;
	else if (InString[0] == '=')
		Type = TokenType::VariableAssignment;
	else if (InString[0] == '(')
		Type = TokenType::OpeningBracket;
	else if (InString[0] == ')')
		Type = TokenType::ClosingBracket;
	else if (InString[0] == '*' || InString[0] == '/')
		Type = TokenType::MultiplyDivide;
	else if (InString[0] == '+' || InString[0] == '-')
		Type = TokenType::AddSubstract;
	else if (InString[0] >= 'a' && InString[0] <= 'z' || InString[0] >= 'A' && InString[0] <= 'Z' || InString[0] == '_')
		Type = TokenType::Variable;
	else if (InString[0] == '>')
		Type = TokenType::Comparison;
	else if (InString[0] >= '1' && InString[0] <= '9' || InString[0] == '0' || InString[0] == '.')
		Type = TokenType::Number;
	else if (InString[0] == ',')
		Type = TokenType::Seperator;
	else
		std::cout << "[EquationString]: ERROR: could not identify character (" << InString[0] << ")\n";
}

void EquationToken::CollapseOperands(int& InMyPosition, std::deque<EquationToken*>& InAllTokens)
{
	switch (Type)
	{
	case TokenType::OpeningBracket:
	{
		int nOpenBrackets = 0;
		for (int i = InMyPosition; i < InAllTokens.size(); i++)
		{
			if (InAllTokens[i]->Type == TokenType::OpeningBracket)
				nOpenBrackets++;
			else if (InAllTokens[i]->Type == TokenType::ClosingBracket)
				nOpenBrackets--;

			if (nOpenBrackets == 0)
			{
				Operands = std::deque<EquationToken*>(InAllTokens.begin() + InMyPosition + 1, InAllTokens.begin() + i);
				InAllTokens.erase(InAllTokens.begin() + InMyPosition + 1, InAllTokens.begin() + i + 1);
				Type = TokenType::CollapsedBracket;
				break;
			}
		}
		break;
	}
	case TokenType::MultiplyDivide:
	case TokenType::AddSubstract:
	case TokenType::Comparison:
	case TokenType::Seperator:
		Operands.push_back(InAllTokens[InMyPosition - 1]);
		Operands.push_back(InAllTokens[InMyPosition + 1]);
		InAllTokens.erase(InAllTokens.begin() + InMyPosition - 1);
		InAllTokens.erase(InAllTokens.begin() + InMyPosition);
		InMyPosition -= 1;
		break;
	case TokenType::VariableAssignment:
	case TokenType::FunctionAssignment:
	case TokenType::Function:
		Operands.push_back(InAllTokens[InMyPosition + 1]);
		InAllTokens.erase(InAllTokens.begin() + InMyPosition + 1);
	case TokenType::Variable:
		break;
	}
}

ElementID EquationToken::rec_RegisterToken(MathContainer* InRuntime)
{
	//special operand rule for seperators
	for (int i = Operands.size() - 1; i >= 0; i--)
	{
		EquationToken* seperatorOperand = Operands[i];
		if (seperatorOperand->Type == TokenType::CollapsedBracket)
		{
			seperatorOperand = seperatorOperand->Operands[0];
		}
		if (seperatorOperand->Type == TokenType::Seperator)
		{
			Operands[i] = seperatorOperand->Operands[1];
			Operands.insert(Operands.begin() + i, seperatorOperand->Operands[0]);
			i++;
		}
	}

	// predefine function
	if (Type == TokenType::FunctionAssignment)
	{
		std::string name;
		for (int i = 0; i < String.size(); i++)
		{
			if (String[i] != '(')
				name += String[i];
			else
				break;
		}
		if (! InRuntime->GetElement<Value>(name))
		{
			InRuntime->Register(new Constant(0), name);
		}
	}

	// get ids of my operands
	std::vector<ElementID> operandIDs;
	for (auto operand : Operands)
	{
		ElementID operandID = operand->rec_RegisterToken(InRuntime);
		operandIDs.push_back(operandID);
	}

	switch (Type)
	{
	case TokenType::CollapsedBracket:
		assert(operandIDs.size() == 1);
		return operandIDs[0];
	case TokenType::MultiplyDivide:
		if (String == "*")
			return InRuntime->Register(new OP_Multiply(operandIDs));
		else if (String == "/")
			return InRuntime->Register(new OP_Divide(operandIDs));
	case TokenType::AddSubstract:
		if (String == "+")
			return InRuntime->Register(new OP_Add(operandIDs));
		else if (String == "-")
			return InRuntime->Register(new OP_Substract(operandIDs));
	case TokenType::Comparison:
		if (String == ">")
			return InRuntime->Register(new OP_GreaterThan(operandIDs));
	case TokenType::Number:
		return InRuntime->Register(new Constant(std::atof(String.c_str())));
	case TokenType::VariableAssignment:
	{
		assert(operandIDs.size() == 1);
		InRuntime->SetValueName(operandIDs[0], std::string(String.begin(), String.end() - 1));
		return operandIDs[0];
	}
	case TokenType::FunctionAssignment:
	{
		assert(operandIDs.size() == 1);
		std::string name;
		for (int i = 0; i < String.size(); i++)
		{
			if (String[i] != '(')
				name += String[i];
			else
				break;
		}
		// redefine preregistered function
		auto preFunc = InRuntime->GetElement<Value>(name);
		auto id = InRuntime->ReRegister(preFunc->GetID(), InRuntime->GetElement<Value>(operandIDs[0]));
		return id;
	}
	case TokenType::Variable:
	{
		Value* foundVariable = InRuntime->GetElement<Value>(String);
		if (foundVariable)
		{
			return foundVariable->GetID();
		}
		else
		{
			std::cout << "could not find variable " << String << std::endl;
			return ElementID();
		}
	}
	case TokenType::Function:
	{
		Value* foundFunction = InRuntime->GetElement<Value>(String);
		if (foundFunction)
		{
			std::vector<ElementID> arguments;
			arguments.push_back(foundFunction->GetID());
			arguments.push_back(operandIDs[0]);
			return InRuntime->Register(new OP_CalculateFunction(InRuntime->FuncCache, arguments));
		}
		else
		{
			if (String == "sel")
			{
				return InRuntime->Register(new OP_Select(operandIDs));
			}
			else
			{
				std::cout << "could not find function " << String << std::endl;
				return ElementID();
			}
		}
	}
	case TokenType::FunctionArgument0:
	{
		ElementID id;
		id.UniqueIdentifier = 0;
		return id;
	}
	default:
	{
		ElementID id;
		return id;
	}
	}
}
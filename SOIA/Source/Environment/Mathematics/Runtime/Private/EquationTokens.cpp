
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/Mathematics/Runtime/Public/EquationTokens.h"
using namespace Environment;

#include <iostream>

//########################################################### TOKENS ##################################
EquationTokens::EquationTokens(const std::vector<std::string>& InFormalParts)
{
	for (auto part : InFormalParts)
	{
		UnsortedTokens.push_back(new EquationToken(part));
	}
}

EquationToken* EquationTokens::GenerateOperandDependency()
{
	/////////////////////////////////////////////////////////////
	// remove whitespaces
	for (auto iter = UnsortedTokens.begin(); iter < UnsortedTokens.end(); iter++)
	{
		if ((*iter)->Type == TokenType::WhiteSpace)
		{
			UnsortedTokens.erase(iter);
		}
	}

	/////////////////////////////////////////////////////////////
	// combine tokens

	// change variable names to functions if followed by brackets
	for (auto iter = UnsortedTokens.begin(); iter < UnsortedTokens.end() - 1; iter++)
	{
		EquationToken* token = (*iter);
		if (token->Type == TokenType::Variable)
		{
			EquationToken* nextToken = *(iter + 1);
			if (nextToken->Type == TokenType::OpeningBracket)
			{
				token->Type = TokenType::Function;
			}
		}
	}

	//combine e numbers (1e-10)
	for (auto iter = UnsortedTokens.begin(); iter < UnsortedTokens.end() - 2; iter++)
	{
		EquationToken* token = (*iter);
		EquationToken* nextToken = *(iter + 1);
		EquationToken* nextNextToken = *(iter + 2);
		if (token->Type == TokenType::Number && (nextToken->String == "e"))
		{
			if (nextNextToken->Type == TokenType::Number)
			{
				token->String += nextToken->String + nextNextToken->String;
				UnsortedTokens.erase(iter + 1, iter + 2);
			}
			else if (nextNextToken->String == "-" && iter < UnsortedTokens.end() - 3 && (*(iter+3))->Type == TokenType::Number)
			{
				token->String += nextToken->String + nextNextToken->String + (*(iter + 3))->String;
				UnsortedTokens.erase(iter + 1, iter + 3);
			}
		}
	}

	// combine variable/function names and assignments
	for (auto iter = UnsortedTokens.begin(); iter < UnsortedTokens.end(); iter++)
	{
		if ((*iter)->Type == TokenType::VariableAssignment)
		{
			EquationToken* name = *(iter - 1);
			if (name->Type == TokenType::Variable) // name is name of variable => a=
			{
				(*iter)->String = name->String + (*iter)->String;
				UnsortedTokens.erase(iter - 1);
				delete name;
			}
			else if (name->Type == TokenType::ClosingBracket) // name is name of function => f(x)=
			{
				(*iter)->Type = TokenType::FunctionAssignment;
				auto functionName_iter = iter;

				// set function assignment name & get function argument names
				std::string functionName = "";
				std::vector<std::string> functionArgNames;
				for (functionName_iter; functionName_iter > UnsortedTokens.begin(); functionName_iter--)
				{
					functionName = (*functionName_iter)->String + functionName;

					//check for end of bracket
					if ((*functionName_iter)->Type == TokenType::OpeningBracket)
					{
						(*iter)->String = (*(functionName_iter - 1))->String + functionName + (*iter)->String;
						UnsortedTokens.erase(functionName_iter - 1, iter);
						// @ToDo: delete all erased tokens
						break;
					}

					if ((*functionName_iter)->Type == TokenType::Variable)
					{
						functionArgNames.push_back((*functionName_iter)->String);
					}
				}

				// scan rest of equation and replace variable-tokentypes with functionArg-tokentypes
				for (auto sub_iter = iter; sub_iter < UnsortedTokens.end(); sub_iter++)
				{
					if ((*sub_iter)->Type == TokenType::Variable)
					{
						if ((*sub_iter)->String == functionArgNames[0])
						{
							(*sub_iter)->Type = TokenType::FunctionArgument0;
						}
					}
				}
			}
			else
			{
				std::cout << "No variable name in front of assignment token!" << std::endl;
				(*iter)->String = "NoName";
			}
		}
	}

	/////////////////////////////////////////////////////////////
	// check for '('

	std::deque<std::deque<EquationToken*>* > TokenLists;
	TokenLists.push_back(&UnsortedTokens);

	for (int i = 0; i < TokenLists.size(); i++)
	{
		auto Tokens = TokenLists[i];
		for (int j = 0; j < Tokens->size(); j++)
		{
			auto Token = (*Tokens)[j];
			if (Token->Type == TokenType::OpeningBracket)
			{
				Token->CollapseOperands(j, *Tokens);
				TokenLists.push_front(&Token->Operands);
				i = -1;
				break;
			}
		}
		if (i > -1)
		{
			MultDivAddSubstDependency(*Tokens);
			VarAssignmentDependency(*Tokens);
		}
	}

	/////////////////////////////////////////////////////////7
	// create name token
	return (*(*(TokenLists.end() - 1))->begin());
}

EquationToken* EquationTokens::MultDivAddSubstDependency(std::deque<EquationToken*>& TokenList)
{

	// check for function calls

	for (int i = 0; i < TokenList.size(); i++)
	{
		auto token = TokenList[i];
		if (token->Type == TokenType::Function)
		{
			token->CollapseOperands(i, TokenList);
		}
	}

	// 1st step: check for * and /

	for (int i = 0; i < TokenList.size(); i++)
	{
		auto token = TokenList[i];
		if (token->Type == TokenType::MultiplyDivide)
		{
			token->CollapseOperands(i, TokenList);
		}
	}

	// th step: check for + and -

	for (int i = 0; i < TokenList.size(); i++)
	{
		auto token = TokenList[i];
		if (token->Type == TokenType::AddSubstract)
		{
			token->CollapseOperands(i, TokenList);
		}
	}


	// check for '>'
	for (int i = 0; i < TokenList.size(); i++)
	{
		auto token = TokenList[i];
		if (token->Type == TokenType::Comparison)
		{
			token->CollapseOperands(i, TokenList);
		}
	}

	return TokenList[0];
}

EquationToken* EquationTokens::VarAssignmentDependency(std::deque<EquationToken*>& TokenList)
{
	



	// check for seperators
	for (int i = 0; i < TokenList.size(); i++)
	{
		auto token = TokenList[i];
		if (token->Type == TokenType::Seperator)
		{
			token->CollapseOperands(i, TokenList);
		}
	}

	// check for variable assignments:
	for (int i = 0; i < TokenList.size(); i++)
	{
		auto token = TokenList[i];
		if (token->Type == TokenType::VariableAssignment)
		{
			token->CollapseOperands(i, TokenList);
		}
	}


	// check for function assignments:
	for (int i = 0; i < TokenList.size(); i++)
	{
		auto token = TokenList[i];
		if (token->Type == TokenType::FunctionAssignment)
		{
			token->CollapseOperands(i, TokenList);
		}
	}

	

	


	return TokenList[0];
}
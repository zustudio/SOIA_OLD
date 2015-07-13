
#include "Definitions.h"

#include "Token.h"
using namespace Environment;

#include "TokenRule.h"

Token::Token(const std::string & InText, Token* InParent, TokenRule* InRule)
	:
	Parent(InParent),
	Text(InText),
	Rule(InRule)
{}

void Token::Move(Token* Target)
{
	auto myIter = std::find(Parent->SubTokens.begin(), Parent->SubTokens.end(), this);
	Parent->SubTokens.erase(myIter);
	Target->SubTokens.push_back(this);
	Parent = Target;
}

void Token::Disable()
{
	auto myIter = std::find(Parent->SubTokens.begin(), Parent->SubTokens.end(), this);
	Parent->SubTokens.erase(myIter);
	Parent = nullptr;
}

std::vector<Token*>& Token::GetSubTokens()
{
	return SubTokens;
}

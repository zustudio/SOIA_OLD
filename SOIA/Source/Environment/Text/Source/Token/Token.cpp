
#include "Definitions.h"

#include "Token.h"
using namespace Environment;

#include "TokenRule.h"

Token::Token(const std::string & InText, TokenArityInterface const * InCollapser, int InRuleIdentifier)
	:
	Text(InText),
	TokenCollapser(InCollapser),
	ContainerIteratorSet(nullptr),
	RuleIdentifier(InRuleIdentifier),
	SubTokens({}),
	ParentToken(nullptr)
{}

void Token::Move(Token * InToken)
{
	Internal_MoveToList(InToken->GetSubTokens());
	ParentToken = InToken;
}

void Token::MoveToList(std::list<Token*> & InOutTargetList)
{
	Internal_MoveToList(InOutTargetList);
	ParentToken = nullptr;
}

void Token::Internal_MoveToList(std::list<Token*>& InOutTargetList)
{
	if (ContainerIteratorSet)
	{
		ContainerIteratorSet->Container.erase(ContainerIteratorSet->Current);
		delete ContainerIteratorSet;
	}

	InOutTargetList.push_back(this);
	ContainerIteratorSet = new ContainerAwareIteratorSet<std::list<Token*>>(InOutTargetList, --InOutTargetList.end());
}

void Token::Disable()
{
	ContainerIteratorSet->Container.erase(ContainerIteratorSet->Current);
}

Token * Token::GetParentToken()
{
	return ParentToken;
}

std::list<Token*>& Token::GetSubTokens()
{
	return SubTokens;
}

std::vector<Token*> Token::GetSubTokenVector()
{
	return std::vector<Token*>(SubTokens.begin(), SubTokens.end());
}

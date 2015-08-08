
#include "Definitions.h"

#include "Token.h"
using namespace Environment;

#include "TokenRule.h"

Token::Token(const std::string & InText, TokenArityInterface const * InCollapser)
	:
	Text(InText),
	TokenCollapser(InCollapser),
	ContainerIteratorSet(nullptr)
{}

void Token::Move(Token * InToken)
{
	Move(InToken->GetSubTokens());
}

void Token::Move(std::list<Token*> & InOutTargetList)
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

std::list<Token*>& Token::GetSubTokens()
{
	return SubTokens;
}

std::vector<Token*> Token::GetSubTokenVector()
{
	return std::vector<Token*>(SubTokens.begin(), SubTokens.end());
}

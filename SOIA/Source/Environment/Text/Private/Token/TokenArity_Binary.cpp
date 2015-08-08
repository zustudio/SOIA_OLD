
#include "Definitions.h"

#include "TokenArity_Binary.h"
using namespace Environment;

#include "Token.h"

bool TokenArity_Binary::Collapse(Token * InToken)
{
	auto iter_leftToken = InToken->ContainerIteratorSet->Current;
	auto iter_rightToken = InToken->ContainerIteratorSet->Current;
	Token* leftToken = *(--iter_leftToken);
	Token* rightToken = *(++iter_rightToken);

	leftToken->Move(InToken);
	rightToken->Move(InToken);

	return true;
}

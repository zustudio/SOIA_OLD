
#pragma once

#include "TokenArityInterface.h"

namespace Environment
{
	class LIBIMPEXP TokenArity_Binary : public TokenArityInterface
	{
	public:
		virtual bool Collapse(Token* InToken) override;
	};
}
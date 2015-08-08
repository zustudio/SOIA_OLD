
#pragma once

#include <list>

namespace Environment
{
	class Token;
	
	class TokenArityInterface
	{
	public:
		virtual bool Collapse(Token* InToken) = 0;
	};
}
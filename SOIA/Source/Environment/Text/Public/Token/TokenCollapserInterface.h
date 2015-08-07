
#pragma once

#include <list>

namespace Environment
{
	class Token;
	
	class TokenCollapserInterface
	{
	public:
		virtual bool Collapse(Token* InToken) = 0;
	};
}
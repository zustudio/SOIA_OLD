
#pragma once

#include <vector>

namespace Environment
{
	class Token;
	
	class TokenCollapseInterface
	{
	public:
		virtual bool Collapse(const Iterators<std::vector<Token*>>& InIters) = 0;
	};
}
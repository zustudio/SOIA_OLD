
#pragma once

#include "TokenCollapseInterface.h"

namespace Environment
{
	class LIBIMPEXP TokenCollapseNone : public TokenCollapseInterface
	{
		virtual bool Collapse(const Iterators<std::vector<Token*>>& InIters) override;
	};
}
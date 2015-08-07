
#pragma once

#include "TokenCollapserInterface.h"

namespace Environment
{
	class LIBIMPEXP TokenCollapserNone : public TokenCollapserInterface
	{
		virtual bool Collapse(Token*) override;
	};
}
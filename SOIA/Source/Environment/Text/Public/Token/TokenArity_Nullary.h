
#pragma once

#include "TokenArityInterface.h"

namespace Environment
{
	class LIBIMPEXP TokenArity_Nullary : public TokenArityInterface
	{
		virtual bool Collapse(Token*) override;
	};
}
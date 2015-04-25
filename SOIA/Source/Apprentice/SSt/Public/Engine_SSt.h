
#pragma once

#include "Apprentice/Core/Public/Engine.h"

namespace Apprentice
{
	class DLLIMPEXP Engine_SSt : public Engine
	{
	public:
		Engine_SSt(Environment::RContainer &InServiceContainer);

		virtual void Init() override;
		virtual void Tick() override;
	};
}
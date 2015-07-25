
#pragma once

#include "RDialogue.h"

namespace Supervisor
{
	class PersistentRuntime
	{
	public:
		static void Initialize(RDialogue& InStandardDialogue);
	};
}

#pragma once

#include "Environment/Reflection/Element/Public/RApplication.h"
#include "Environment/Event/Public/Event.h"


namespace Supervisor
{
	class DLLIMPEXP SchroedingerApplication : public Environment::RApplication
	{
	public:
		SchroedingerApplication(Environment::RContainer &InServiceContainer);
		virtual void Main() override;

		bool eventhandler_ButtonPressed(Environment::EventDetails*);
	};
}
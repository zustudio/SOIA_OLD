
#pragma once

#include "TTool.h"
#include "Thread.h"

namespace Supervisor
{
	RABSTRACTCLASS(TMainTool, TTool)
	class LIBIMPEXP TMainTool : public TMainTool_Base, public Env::Thread
	{
		RCLASS_BEGIN()

	public:
		///\name ctor
		///\{
			TMainTool();
		///\}

	protected:
		///\name tool configuration
		///\{
			void ConfigureMainTool(DialogueInterface* InDialogue);
		///\}
		
		RCLASS_END()
	};
}
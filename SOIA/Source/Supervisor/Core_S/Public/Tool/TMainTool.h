
#pragma once

#include "TTool.h"
#include "Thread.h"
#include "Tokenizer.h"
#include "DialogueInterface.h"

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
			void ConfigureMainTool(Env::DialogueInterface* InDialogue);
		///\}

		///\name command parsing
		///\{
			bool ExecuteString(std::string InString);
			bool ExecuteCommands(std::list<Env::Token*> const & Input, std::vector<Env::VoidPointer>& OutArguments);
			bool ExecuteCommand(const std::string& InTarget, std::string& InCommand, std::vector<Env::VoidPointer>& InOutArguments);
		///\}

	private:
		///\name command parsing
		///\{
			Env::Tokenizer InputTokenizer;
		///\}
		
		RCLASS_END()
	};
}

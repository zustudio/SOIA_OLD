
#pragma once

#include "ICmd.h"

#include <vector>

#include "Handle.h"
#include "ICom.h"
//#include "IIComIO.h"


using namespace SO::Base;

namespace SOIA
{
	class ConsoleService;
}

namespace SO
{
	namespace Com
	{
		class ComService/* : public SO::Com::IIComIO*/
		{
			friend class SOIA::ConsoleService;

		public:
			/////////////////////////////////////////////////
			// init 
			ComService();

			/////////////////////////////////////////////////
			// management
			void Register(Handle<ICom> &Com, bool bForceNoNameCheck = false);
			void AdjustComName(Handle<ICom> &Com);
			bool TranslateString(const std::string &Target, const std::vector<std::string> &Args, std::vector<Handle<ICom> > &outTargets, Handle<ICmd> &outCmd, std::vector<VoidPointer> &outArgs);

			/////////////////////////////////////////////////
			// message distribution
			bool Forward(const Handle<ICom> &Target, const Handle<ICom> &Caller, const ICmd &Command, const std::vector<VoidPointer> &Args);

			/////////////////////////////////////////////////
			// ICom
			//---- commands ----
			//bool cmd_ToggleVerbose(const std::vector<VoidPointer> &Args);
			////---- implementation ----
			//virtual void cGetCommands(std::vector<Handle<ICmd> > &Commands) override;

		private:
			/////////////////////////////////////////////////
			// variables
			std::vector<Handle<ICom> > Communicators;
			bool bVerbose;
		};
	}
}

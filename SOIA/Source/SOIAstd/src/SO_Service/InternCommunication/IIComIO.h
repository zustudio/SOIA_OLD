
#pragma once

//Super
#include "IIComIn.h"
#include "IIComOut.h"

#include "Handle.h"
#include "Com_Cmd.h"

//vars
#include "ComService.h"

namespace SO
{
	namespace Com
	{
		class IIComIO : public IIComIn, virtual public IIComOut
		{
		public:
			////////////////////////////////////////////////////////
			// publicily accessed functions
			IIComIO(ComService* NewComService);
			virtual Handle<ICom>& cGetHandle();
			virtual void cGetCommands(std::vector<Handle<ICmd> > &Commands);

			T_com_cmd_func cmd_help;

		protected:
			////////////////////////////////////////////////////////
			// Improvements over IIComIn & IIComOut
			//---- Common ----
			void TryCreateHandle(const std::string &Name);
			//---- OUT ----
			virtual bool cSend(const Handle<ICom> &Target, const ICmd &Command, const std::vector<VoidPointer> &Args);
			virtual bool cSend(const std::string &Target, const std::string &Command, const std::vector<VoidPointer> &Args);
			virtual bool cSend(const std::string &Target, const std::string &Command, const std::string &Arg1 = "", const std::string &Arg2 = "", const std::string &Arg3 = "", const std::string &Arg4 = "", const std::string &Arg5 = "");

			////////////////////////////////////////////////////////
			// variables
			//---- upstream ----
			ComService* Up;
		private:
			Handle<ICom>* Hndl;
		};
	}
}


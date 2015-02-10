
#pragma once

//Super
#include "ICom.h"
//#include "IDebugObj.h"

//vars
#include "ComService.h"

namespace SO
{
	namespace Com
	{
		class IIComIO : public ICom //, public IDebugObj
		{
		public:
			//helper definitions
			typedef bool (T_com_cmd_func)(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args);
			#define ICom_RegisterCmd(list, classT, func, name) list.push_back(SO::Base::Handle<SO::Base::ICmd>(new SO::Com::Com_Cmd<classT>(&classT::func), std::string(name)));

			////////////////////////////////////////////////////////
			// publicily accessed functions
			IIComIO(ComService* NewComService);
			virtual Handle<ICom>& cGetHandle();

		protected:
			////////////////////////////////////////////////////////
			// implementation of ICom functionality for child classes
			virtual bool cSend(const Handle<ICom> &Target, const ICmd &Command, const std::vector<VoidPointer> &Args) override;
			virtual bool cSend(const std::string &Target, const std::string &Command, const std::vector<VoidPointer> &Args);
			virtual bool cSend(const std::string &Target, const std::string &Command, const std::string &Arg1 = "", const std::string &Arg2 = "", const std::string &Arg3 = "", const std::string &Arg4 = "", const std::string &Arg5 = "");

			////////////////////////////////////////////////////////
			// helpers
			void TryCreateHandle(const std::string &Name);

			////////////////////////////////////////////////////////
			// variables
			//---- upstream ----
			ComService* Up;
		private:
			Handle<ICom>* Hndl;
		};
	}
}


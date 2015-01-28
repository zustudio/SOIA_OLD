
#pragma once

//Super
#include "ICom.h"

//vars
#include "ComService.h"

namespace SO
{
	namespace Com
	{
		class IIComIO : public ICom
		{
		public:
			//helper definitions
			typedef bool (T_com_cmd_func)(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args);
#define ICom_RegisterCmd(list, classT, func, name) list.push_back(SO::Base::Handle<SO::Base::ICmd>(new SO::Com::Com_Cmd<classT>(&classT::func), std::string(name)));
#define ICom_GetSingleArg(TYPE, VARNAME, INARGS, NUM, ExitOnFail)	TYPE* VARNAME; \
																	{ \
																		bool bGetArgMacroFailed = false; \
																		VARNAME = cGetArg<TYPE>(INARGS, NUM, bGetArgMacroFailed); \
																		if ((ExitOnFail) && bGetArgMacroFailed) {return false;} \
																	}

			////////////////////////////////////////////////////////
			// publicily accessed functions
			IIComIO(ComService* NewComService);

		protected:
			////////////////////////////////////////////////////////
			// implementation of functionality for child classes
			virtual bool cSend(const Handle<ICom> &Target, const ICmd &Command, const std::vector<VoidPointer> &Args) override;
			virtual Handle<ICom>& cGetHandle();
			template<typename T> T* cGetArg(const std::vector<VoidPointer> &Args, int i, bool &bFailed)
			{
				T* result = nullptr;
				if (i < Args.size())
				{
					result = Args[i].CastTo<T>();
					if (!result)
					{
						bFailed |= true;
					}
				}
				else
				{
					bFailed |= true;
				}
				return result;
			}

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


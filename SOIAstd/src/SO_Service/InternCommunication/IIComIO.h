
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
			typedef bool (T_com_cmd_func)(const Handle<ICom> &Caller, const std::vector<void*> &Args);
			#define ICom_RegisterCmd(list, classT, func, name) list.push_back(SO::Base::Handle<SO::Base::ICmd>(new SO::Com::Com_Cmd<classT>(&classT::func), std::string(name)));

			////////////////////////////////////////////////////////
			// publicily accessed functions
			IIComIO(ComService* NewComService);

		protected:
			////////////////////////////////////////////////////////
			// implementation of functionality for child classes

			virtual bool cSend(const Handle<ICom> &Target, const ICmd &Command, const std::vector<void*> &Args) override;
			virtual Handle<ICom>& cGetHandle();

			////////////////////////////////////////////////////////
			// helpers
			template<typename T>
			void TryCreateHandle(const std::string &Name)
			{
				if (!Hndl)
				{
					//T* cast = dynamic_cast<T*>(this);
					
					Hndl = new Handle<ICom>(/*dynamic_cast<ICom*>(*/this/*)*/, Name);
				}
			}

			////////////////////////////////////////////////////////
			// variables
			//---- upstream ----
			ComService* Up;
		private:
			Handle<ICom>* Hndl;
		};
	}
}



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
			typedef bool (T_com_cmd_func)(const Handle<ICom> &Caller, const std::vector<void*> &Args);

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


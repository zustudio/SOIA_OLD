
#pragma once

//Super
#include "ICmd.h"

#include "ICom.h"
#include "Handle.h"

namespace SO
{
	namespace Com
	{
		template<typename TargetC>
		class Com_Cmd : public SO::Base::ICmd
		{
			//////////////////////////////////////////////////////////////////////////////////////
			// definitions
			//typedef bool(TargetC::* TargetFuncType) (const SO::Base::Handle<ICom> &Caller, const std::vector<void*> &Args);
			using T_com_cmd_func = bool (TargetC::*) (const SO::Base::Handle<ICom> &Caller, const std::vector<void*> &Args);

		public:
			//////////////////////////////////////////////////////////////////////////////////////
			// public callable
			//---- init ----
			Com_Cmd(T_com_cmd_func NewFunc)	{ Cmd = NewFunc; }
			//---- exec ----
			virtual bool Execute(void* TargetObject, void* Caller, const std::vector<void*> &Args) const override
			{
				TargetC* targetObject = static_cast<TargetC*>(reinterpret_cast<ICom*>(TargetObject));
				SO::Base::Handle<SO::Com::ICom>* caller = (SO::Base::Handle<SO::Com::ICom>*)Caller;
				return ((targetObject)->*Cmd)(*caller, Args);
			}

		private:
			//////////////////////////////////////////////////////////////////////////////////////
			// private properties
			//---- target ----
			T_com_cmd_func Cmd;
		};
	}
}

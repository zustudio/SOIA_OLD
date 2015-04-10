
#pragma once

//Super interface
#include "ICom.h"

//for getCommands
#include "Com_Cmd.h"

namespace SO
{
	namespace Com
	{
		using namespace SO::Base;
		class IIComIn : public virtual ICom
		{
		public:
			/////////////////////////////////////////////////////////////////////////////////
			// definitions
			//---- command helpers ----
			typedef bool (T_com_cmd_func)(const Handle<ICom> &Caller, const std::vector<VoidPointer> &Args);
			#define ICom_RegisterCmd(list, classT, func, name) list.push_back(SO::Base::Handle<SO::Base::ICmd>(new SO::Com::Com_Cmd<classT>(&classT::func), std::string(name)));
			
			/////////////////////////////////////////////////////////////////////////////////
			// functions
			//---- publicily accessible properties ----
			/**
			 * First implementation of getCommands, registers common commands. To be overriden and super::called by child classes.
			 */
			virtual void cGetCommands(std::vector<Handle<ICmd> > &Commands) override;
		};
	}
}
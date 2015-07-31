
#pragma once

#include "TTool.h"

namespace Supervisor
{
	RCLASS(TElementExplorer,TTool)
	class LIBIMPEXP TElementExplorer : public TElementExplorer_Base
	{
		RCLASS_BEGIN()

		TElementExplorer();

		RFUNCTION(cmd_ls)
			bool cmd_ls();

		RFUNCTION(cmd_pwd)
			bool cmd_pwd(Environment::RContainer*&);

		RFUNCTION(cmd_elem)
			bool cmd_elem(RElement*& OutElement, const std::string& InName);

		RFUNCTION(cmd_cc)
			bool cmd_cc(const std::string& InContainerName);

		RFUNCTION(cmd_attrlist)
			bool cmd_attrlist(RElement* const & InElement, std::string const & InAttributeName);

		RFUNCTION(cmd_func)
			bool cmd_func(RFunction* & OutFunction, RElement* const& InElement, std::string const& InFuncName);

		std::string GetCurrentPath();

		Environment::RContainer* CurrentContainer;

		RCLASS_END()
	};
}

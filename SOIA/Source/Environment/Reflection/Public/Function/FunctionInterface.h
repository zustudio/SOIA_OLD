
#pragma once

#include "Definitions.h"

#include "Atom.h"
#include "VoidPointer.h"

#include <vector>

namespace Environment
{
	class LIBIMPEXP FunctionInterface : public Atom
	{
	public:
		virtual bool Execute(const std::vector<VoidPointer> &InArgs) {return false;}
		virtual std::vector<TypeID> GetArgumentTypes() { return{}; }

		static std::string ToString(const FunctionInterface& InID)
		{
			return "";
		}
		static FunctionInterface FromString(const std::string& InString)
		{
			return FunctionInterface();
		}
	};
}

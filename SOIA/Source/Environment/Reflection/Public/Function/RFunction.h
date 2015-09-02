
#pragma once

#include "Definitions.h"

#include "Atom.h"
#include "VoidPointer.h"

#include <vector>

namespace Environment
{
	class LIBIMPEXP RFunction : public Atom
	{
	public:
		virtual bool Execute(const std::vector<VoidPointer> &InArgs) {return false;}
		virtual std::vector<TypeID> GetArgumentTypes() { return{}; }
		virtual std::string GetName() { return ""; };

		bool CorrectArgsAndExecute(std::vector<VoidPointer> &InArgs);

		static std::string StaticToString(const RFunction& InID)
		{
			return "";
		}
		static RFunction StaticToObject(const std::string& InString)
		{
			return RFunction();
		}
	};
}

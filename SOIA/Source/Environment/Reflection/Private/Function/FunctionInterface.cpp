
#include "Definitions.h"

#include "FunctionInterface.h"
using namespace Environment;

#include "ReflectionProviders.h"
#include "LogProvider.h"

bool FunctionInterface::CorrectArgsAndExecute(std::vector<VoidPointer> &CorrectedArgs)
{
	std::vector<TypeID> wantedTypes = GetArgumentTypes();
	std::vector<VoidPointer> inArgs = CorrectedArgs;
	CorrectedArgs.clear();

	for (auto wantedType : wantedTypes)
	{
		bool bfound = false;
		for (auto arg : inArgs)
		{
			if ((arg.IsChildOf(wantedType.Decay()) || arg.GetTypeID().Decay() == wantedType.Decay()) && std::find(CorrectedArgs.begin(), CorrectedArgs.end(), arg/*, [&arg](const VoidPointer& p) {return p == arg; }*/) == CorrectedArgs.end())
			{
				CorrectedArgs.push_back(arg);
				bfound = true;
				break;
			}
		}
		if (!bfound)
		{
			VoidPointer defaultAtom = *GetAtomReflectionProvider()->GetReflection(wantedType.Decay())->StringToObject("");
			if (defaultAtom.GetTypeID() == TypeID::FromType<RPointer>())
			{
				//RElement* p_element = defaultAtom.CastAndDereference<RPointer>().Resolve();
				CorrectedArgs.push_back(*new RElement*(nullptr));
				CorrectedArgs[CorrectedArgs.size() - 1].OverrideType(wantedType.Decay());
			}
			else
			{
				CorrectedArgs.push_back(defaultAtom);
			}
		}
	}
	if (CorrectedArgs.size() != wantedTypes.size())
	{
		LOG("Arguments for calling function interface did not match and could not be corrected.", Logger::Severity::Warning);
		return false;
	}
	else
	{
		bool result = Execute(CorrectedArgs);
		return result;
	}
}
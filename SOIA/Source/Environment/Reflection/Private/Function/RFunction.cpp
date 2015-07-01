
#include "Definitions.h"

#include "RFunction.h"
using namespace Environment;

#include "ReflectionProviders.h"
#include "LogProvider.h"

bool RFunction::CorrectArgsAndExecute(std::vector<VoidPointer> &CorrectedArgs)
{
	std::vector<TypeID> wantedTypes = GetArgumentTypes();
	std::vector<VoidPointer> inArgs = CorrectedArgs;
	std::vector<int> defaultCreatedArgs;
	CorrectedArgs.clear();

	for (auto wantedType : wantedTypes)
	{
		bool bfound = false;
		for (auto iter_arg = inArgs.begin(); iter_arg != inArgs.end(); iter_arg++)
		{
			if (((*iter_arg).IsChildOf(wantedType.Decay()) || (*iter_arg).GetTypeID().Decay() == wantedType.Decay()) && std::find(CorrectedArgs.begin(), CorrectedArgs.end(), (*iter_arg)) == CorrectedArgs.end())
			{
				CorrectedArgs.push_back(*iter_arg);
				iter_arg = inArgs.erase(iter_arg);
				bfound = true;
				break;
			}
		}
		if (!bfound)
		{
			VoidPointer defaultAtom = VoidPointer::Nullpointer();
			defaultAtom.OverrideType(wantedType);
			CorrectedArgs.push_back(defaultAtom);
			defaultCreatedArgs.push_back(CorrectedArgs.size() - 1);
		}
	}

	int n = defaultCreatedArgs.size();
	for (int i = 0; i < n; i++)
	{
		std::string translation = "";
		if (inArgs.size())
		{
			translation = GetAtomReflectionProvider()->GetReflection(inArgs[i].GetTypeID().Decay())->ObjectToString(inArgs[i]);
		}

		VoidPointer createdAtom = *GetAtomReflectionProvider()->GetReflection(CorrectedArgs[defaultCreatedArgs[i]].GetTypeID().Decay())->StringToObject(translation);

		CorrectedArgs[defaultCreatedArgs[i]] = createdAtom;
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
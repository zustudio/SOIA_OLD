
#pragma once

#include "RTypedPointer.h"

#include "RElement.h"

namespace Environment
{
	template<class RElementClass>
	class RTypedPointer : public RPointer
	{
	public:
		RTypedPointer(RElement* InElement, const TypeID& InTypeID)
			: RPointer(InElement, InTypeID)
		{}
		RTypedPointer(int InID, const TypeID& InTypeID)
			: RPointer(InID, InTypeID)
		{}

		static RTypedPointer FromString(const std::string& InString)
		{
			auto result = MatchPattern(InString, "(-?[0-9]+),(\\w+)::(\\w+)\\*");
			if (result.size() == 4)
			{
				std::string ID = result[1];
				std::string Type = result[2] + "::" + result[3] + "*";
				return RTypedPointer(std::atoi(ID.c_str()), TypeID(Type));
			}
			return RTypedPointer(-1, TypeID(""));
		}

		static std::string ToString(const RTypedPointer& InObject)
		{
			return std::to_string(InObject.Target.UniqueIdentifier) + "," + std::string(InObject.Type);
		}

		RElementClass* Resolve()
		{
			RElementClass* result = nullptr;
			if (Container)
			{
				result = Container->GetElement<RElementClass>(Target);
			}
			return result;
		}
	};
}
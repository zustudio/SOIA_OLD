// Here come typedefs and macros used for easier code writing

#pragma once

#include <vector>
#include <string>

/* custom extendable enum class */
#define ExtendableEnum(enumname, operations) class enumname {private: int i; public: enumname(int newI = 0) { i = newI; } operator int() { return i; } operations }
#define ExtendableEnumElement(name, var) static const int name = var

namespace Environment
{
	/* custom depth std::find*/
	template<typename ListType, typename TargetObjectType>
	auto Find(const ListType& InList, const TargetObjectType& InTargetObject, TargetObjectType&(*AccessorFunction)(const typename ListType::value_type&), bool) -> decltype(std::declval<const ListType&>().begin())
	{
		auto iter = InList.begin();
		for (iter; iter != InList.end(); iter++)
		{
			if (AccessorFunction(*iter) == InTargetObject)
				break;
		}
		return iter;
	}

	template<typename ListType, typename TargetObjectType, typename AccessorFunctionType>
	auto Find(const ListType& InList, const TargetObjectType& InTargetObject, AccessorFunctionType AccessorFunction) -> decltype(std::declval<const ListType&>().begin())
	{
		return Find<ListType, TargetObjectType>(InList, InTargetObject, AccessorFunction, true);
	}


	
}



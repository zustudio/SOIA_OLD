
#pragma once

#include "Atom.h"

#include "RElement.h"
#include "RContainer.h"
#include "ContainerProvider.h"

namespace Environment
{
	template<class RElementClass = RElement>
	class LIBIMPEXP RPointer : public Atom
	{
	public:
		RPointer(RElementClass* InElement)
			:
			TargetElement(InElement),
			TargetID(InElement ? InElement->GetID() : ElementID()),
			TargetContainer(InElement ? InElement->GetContainer() : nullptr)
		{}

		explicit RPointer(ElementID InID, RContainer* InContainer = nullptr)
			:
			TargetElement(nullptr),
			TargetContainer(InContainer),
			TargetID(InID)
		{}

		RElementClass* GetTargetElement()
		{
			RElementClass* result = nullptr;
			if (TargetElement)
			{
				result = TargetElement;
			}
			else if (TargetContainer || (TargetContainer = GlobalContainer()))
			{
				result = TargetContainer->GetElement<RElementClass>(TargetID);
				TargetElement = result;
			}
			return result;
		}

		decltype(auto) operator-> ()
		{
			return ExposeMemberAccessOperator(GetTargetElement());
		}

		RElementClass* TargetElement;
		ElementID TargetID;
		RContainer* TargetContainer;


		static RPointer FromString(const std::string& InString)
		{
			ElementID id;
			id.UniqueIdentifier = std::atoi(InString.c_str());
			return RPointer(id);
		}
		static std::string ToString(const RPointer& InObject)
		{
			return std::to_string(InObject.TargetID.UniqueIdentifier);
		}
	};
}
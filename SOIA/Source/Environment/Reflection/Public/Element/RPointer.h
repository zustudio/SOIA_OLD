
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
			TargetID(InElement ? InElement->GetID() : Element_ID()),
			TargetContainer(InElement ? InElement->GetContainer() : nullptr)
		{}

		RPointer(Element_ID InID, RContainer* InContainer = nullptr)
			:
			TargetElement(nullptr),
			TargetContainer(InContainer),
			TargetID(InID)
		{}

		RElementClass* Resolve()
		{
			RElementClass* result = nullptr;
			if (TargetElement)
			{
				result = TargetElement;
			}
			else if (TargetContainer || (TargetContainer = GetTopContainer()))
			{
				result = TargetContainer->GetElement<RElementClass>(TargetID);
				TargetElement = result;
			}
			return result;
		}

		RElementClass* operator-> ()
		{
			return Resolve();
		}

		RElementClass* TargetElement;
		Element_ID TargetID;
		RContainer* TargetContainer;


		static RPointer FromString(const std::string& InString)
		{
			Element_ID id;
			id.UniqueIdentifier = std::atoi(InString.c_str());
			return RPointer(id);
		}
		static std::string ToString(const RPointer& InObject)
		{
			return std::to_string(InObject.TargetID.UniqueIdentifier);
		}
	};
}
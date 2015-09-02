/// Intelligence Project - SOIA
/// \file
/// \copyright
///

#pragma once

#include "Atom.h"

#include "RElement.h"
#include "RContainer.h"
#include "GlobalContainer.h"

namespace Environment
{
	enum class ECachingMode : int
	{
		Custom = 0,
		Always = 1
	};

	/// \brief		Custom pointer to RElement using it's ElementID
	/// \details	RPointer resolves the ID when being accessed to the corresponding element.
	template<class RElementClass = RElement>
	class LIBIMPEXP RPointer : public Atom
	{
	public:
		RPointer(RElementClass* InElement, ECachingMode InCachingMode = ECachingMode::Custom)
			:
			Target(InCachingMode == ECachingMode::Always ? InElement : nullptr),
			TargetID(InElement ? InElement->GetID() : ElementID()),
			TargetContainer(InElement ? InElement->GetContainer() : nullptr),
			CachingMode(InCachingMode)
		{}

		RPointer(ElementID InID, RContainer* InContainer, ECachingMode InCachingMode = ECachingMode::Custom)
			:
			Target(nullptr),
			TargetContainer(InContainer),
			TargetID(InID),
			CachingMode(InCachingMode)
		{}

		decltype(auto) operator-> ()
		{
			return ExposeMemberAccessOperator(RawPointer());
		}

		void RecacheTarget()
		{
			Target = nullptr;
			Target = RawPointer();
		}

		RElementClass* RawPointer()
		{
			RElementClass* target = nullptr;
			if (Target)
			{
				target = Target;
			}
			else if (TargetContainer || (TargetContainer = GlobalContainer()))
			{
				target = TargetContainer->GetElement<RElementClass>(TargetID);

				if (CachingMode == ECachingMode::Always)
				{
					Target = target;
				}
			}
			return target;
		}



		static RPointer StaticToObject(const std::string& InString)
		{
			return RPointer(ElementID::StaticToObject(InString));
		}
		static std::string StaticToString(const RPointer& InObject)
		{
			return ElementID::StaticToString(InObject.TargetID);
		}

	private:
		ElementID TargetID;
		RContainer* TargetContainer;
		RElementClass* Target;
		ECachingMode CachingMode;
	};
}
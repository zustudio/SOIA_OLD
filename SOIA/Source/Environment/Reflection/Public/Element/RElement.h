/////////////////////////////////////////////////////////////////////////////////////////////
///	Project:	SOIA
///	Author:		Maxim Urschumzew
/// Year:		2015
///

#pragma once

#include "RElementBase.h"

#include "ElementID.h"
#include "ElementReflection.h"
#include "ElementReflectionProvider.h"
#include "RClassTemplate.h"
#include "RAbstractClass.h"
#include "ObjectMirrorTemplate.h"
#include "ReflectionProviders.h"
#include "ReflectionMacros.h"


namespace Environment
{
	class RContainer;

	struct ElementRegistrationInfo
	{
		ElementRegistrationInfo(RContainer* InContainer, ElementID const & InID, std::string const & InName)
			:
			Container(InContainer),
			ID(InID),
			Name(InName)
		{}

		RContainer* Container;
		ElementID const & ID;
		std::string const & Name;
	};

	RCLASS(RElement,RElementBase)
	class LIBIMPEXP RElement : public RElement_Base
	{
		friend RContainer;

		RCLASS_BEGIN()

		////////////////////////////////////////////////////////////////
		// Functions

		//------------------------------
		//--- Init
	public:
		RElement();
		virtual ~RElement();

		//------------------------------
		//--- Container interaction
	private:
		virtual void Registered(ElementRegistrationInfo const & InInfo);

		//------------------------------
		//--- Access
	public:
		ElementID& GetID();
		RContainer* GetContainer();

		std::vector<std::string> GetAttributeNames();
		ObjectMirror* GetAttribute(const std::string& InName);
		std::vector<ObjectMirror*> const GetAttributes();


		////////////////////////////////////////////////////////////////
		// Variables
	protected:

		RContainer* Container;

		RPROPERTY(ID)
			ElementID ID;

		RPROPERTY(Name)
			std::string Name;

		RCLASS_END()
	};
}

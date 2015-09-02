/// Intelligence Project - SOIA
/// \file
/// \copyright
///

#pragma once

// include super
#include "RElementBase.h"

// include SOIA
#include "ElementID.h"
#include "RClassProvider.h"
#include "RClassTemplate.h"
#include "RAbstractClass.h"
#include "ObjectMirrorTemplate.h"
#include "GlobalReflectionProviders.h"
#include "ReflectionMacros.h"

// forward definitions
namespace Environment
{
	class RContainer;
}



namespace Environment
{
	//////////////////////////////////////////////////////////////////////////////////////////
	/// \struct			ElementRegistrationInfo
	/// \brief			Information passed from RContainer to RElement, when it is being registered.
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

	//////////////////////////////////////////////////////////////////////////////////////////
	/// \class		RElement
	/// \brief		Base class for every reflected (R-)class.
	/// \details	Provides the interface necessary to access reflected attributes of an 
	///				object via their name. Furthermore it interacts with RContainer, in order
	///				to be accessible inside the container hierarchy.
	RCLASS(RElement,RElementBase)
	class LIBIMPEXP RElement : public RElement_Base
	{
		friend RContainer;

		RCLASS_BEGIN()

		////////////////////////////////////////////////////////////////
		// Functions

	public:
		///\name Init
		///\{
			RElement();
			virtual ~RElement();
		///\}

		///\name Access to general element properties
		///\{
			ElementID& GetID();
			std::string& GetName();
			RContainer* GetContainer();
		///\}

		///\name Access to reflected attributes
		///\{
			std::vector<ObjectMirror*> const GetAttributes();
			std::vector<std::string> GetAttributeNames();
			ObjectMirror* GetAttribute(const std::string& InName);
		///\}

	private:
		///\name Container interaction
		///\{
			virtual void Registered(ElementRegistrationInfo const & InInfo);
		///\}


		////////////////////////////////////////////////////////////////
		// Variables

	protected:
		///\name Reflected properties
		///\{
			RPROPERTY(ID)
				ElementID ID;
			RPROPERTY(Name)
				std::string Name;
		///\}

		///\name Unreflected properties
		///\{
			RContainer* Container;
		///\}


		RCLASS_END()
	};
}

/// Intelligence Project - SOIA
/// \file
/// \copyright
///

#pragma once

#include "RElement.h"
#include "ElementID.h"
#include "Range.h"

#include <vector>

namespace Environment
{
	/// \class		RContainer
	/// \brief		Basic container for RElements.
	/// \details	Implements the element-hierarchy. Provides different access methods.
	RCLASS(RContainer,RElement)
	class LIBIMPEXP RContainer : public RContainer_Base
	{
		RCLASS_BEGIN()
		//////////////////////////////////////////////////////////////////
		// Functions

		///\name Init
		///\{
			explicit RContainer(const Range<int>& InAllowedIDs = Range<int>(0,0), const std::vector<RElement*>& InElements = {});
		///\}

		///\name Registration
		///\{
			/// Registers new Object.
			ElementID& Register(RElement* InObject, const std::string &InName="");

			/// Overwrites old registration with a new Object.
			ElementID& ReRegister(const ElementID &InID, RElement* InObject);

			/// Unregisters object.
			void Unregister(RElement* InObject);

			/// Clears reference to contained elements
			/// \todo delete removed elements
			void Clear();
		///\}

		///\name Object Access
		///\{
			/// Returns pointer to pointer to registered Object.
			RElement** GetElementPointer(const ElementID &InID);
			RElement** GetElementPointer(const std::string &InName);

			/// Returns pointer to registered Object.
			template<class RCastClass, class IdentifierType>
			RCastClass* GetElement(const IdentifierType &InID)
			{
				RCastClass* result = nullptr;

				RElement** pointerToElement = GetElementPointer(InID);
				if (pointerToElement)
				{
					RCastClass* element = dynamic_cast<RCastClass*>(*pointerToElement);
					if (element)
					{
						result = element;
					}
				}

				return result;
			}

			/// Returns vector with elements of chosen type.
			template <class RCastClass>
			std::vector<RCastClass*> GetAllElements()
			{
				std::vector<RCastClass*> result;
			
				for (RElement* element : Objects)
				{
					RCastClass* castElement = dynamic_cast<RCastClass*>(element);

					if (castElement)
					{
						result.push_back(castElement);
					}
				}
				return result;
			}

			/// Returns elements with named attribute
			template<class RCastClass, typename AttributeType>
			std::vector<RCastClass*> GetElementsWithAttribute(const std::string& InAttributeName)
			{
				std::vector<RCastClass*> allElements = GetAllElements<RCastClass>();
				std::vector<RCastClass*> result;
				for (auto element : allElements)
				{
					auto p_foundAttribute = element->GetAttribute(InAttributeName);
					if (p_foundAttribute)
					{
						auto foundAttribute = p_foundAttribute->Object().template CastTo<AttributeType>();
						if (foundAttribute)
						{
							result.push_back(element);
						}
					}
				}
				return result;
			}
		///\}

	private:
		///\name Private ID Management
		///\{
			/// Tries to create a new ID in AllowedIDs range.
			ElementID NextFreeID();
			void NextFreeName(std::string &InOutName);
		///\}

	protected:
		//////////////////////////////////////////////////////////////////
		// Variables

		/// Objects that are registered in this container.
		RPROPERTY(Objects)
			std::vector<RElement*> Objects;

		/// Range of IDs this Container is allowed to distribute.
		RPROPERTY(AllowedIDs)
			Range<int> AllowedIDs;

		RCLASS_END()
	};
}

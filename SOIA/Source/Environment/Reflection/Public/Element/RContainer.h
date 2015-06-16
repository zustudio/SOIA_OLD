
#pragma once

#include "RElement.h"
#include "Element_ID.h"
#include "Range.h"

#include <vector>

namespace Environment
{
	RCLASS(RContainer,RElement)
	class LIBIMPEXP RContainer : public RContainer_Base
	{
	public:
		//////////////////////////////////////////////////////////////////
		// Functions

		//----- Initializing -----
		/// Constructor
		RContainer(const Range<int>& InAllowedIDs = Range<int>(0,0), const std::vector<RElement*>& InElements = {});

		//----- Public Object Access -----
		/// Registers new Object.
		Element_ID& Register(RElement* InObject, const std::string &InName="");

		/// Overwrites old registration with a new Object.
		Element_ID& ReRegister(const Element_ID &InID, RElement* InObject);

		/// Unregisters object.
		void Unregister(RElement* InObject);
		void Clear();

		/// Returns pointer to pointer to registered Object.
		RElement** GetElementPointer(const Element_ID &InID);
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
		std::vector<RCastClass*> GetElementsWithAttribute(const std::string InAttributeName)
		{
			std::vector<RCastClass*> allElements = GetAllElements<RCastClass>();
			std::vector<RCastClass*> result;
			for (auto element : allElements)
			{
				auto p_foundAttribute = element->GetAttribute(InAttributeName);
				if (!p_foundAttribute.IsNullPointer())
				{
					auto foundAttribute = p_foundAttribute.template CastTo<AttributeType>();
					if (foundAttribute)
					{
						result.push_back(element);
					}
				}
			}
			return result;
		}

	private:
		//----- Private ID Management -----
		/// Tries to create a new ID in AllowedIDs range.
		Element_ID NextFreeID();
		void NextFreeName(std::string &InOutName);

	protected:
		//////////////////////////////////////////////////////////////////
		// Variables

		/// Objects that are registered in this container.
		std::vector<RElement*> Objects;

		/// Range of IDs this Container is allowed to distribute.
		Range<int> AllowedIDs;
	};
}


#pragma once

#include "RClass.h"

#include <string>

namespace Environment
{
	class RElement;

	template<typename RType>
	class RClassTemplate : public RClass
	{
	public:
		RClassTemplate(const std::string& InTypeID, const std::string& InBaseTypeID)
		{
			TypeID = InTypeID;
			BaseTypeID = InBaseTypeID;
		}

		virtual RElement* GetDefaultObject() override
		{
			return new RType();
		}
		virtual std::string GetType() override
		{
			return TypeID;
		}
		virtual bool IsType(const std::string& InTypeID) override
		{
			return (InTypeID == TypeID);
		}

	private:
		std::string TypeID;
		std::string BaseTypeID;
	};
}
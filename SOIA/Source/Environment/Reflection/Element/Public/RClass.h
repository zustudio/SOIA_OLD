
#pragma once

#include <string>

namespace Environment
{
	class RElement;
	class DLLIMPEXP RClass
	{
	public:
		////////////////////////////////////////////////////////////////
		// Functions
		//----- Initializing -----

		RClass(const std::string& InTypeID, const std::string& InBaseTypeID);
		virtual ~RClass();

		//----- Definitions for child classes -----

		virtual RElement* GetDefaultObject() = 0;
		virtual bool IsAbstract() = 0;

		//----- Type Access -----

		std::string GetType();
		bool IsType(const std::string& InTypeID);


	private:
		////////////////////////////////////////////////////////////////
		// Variables
		std::string TypeID;
		std::string BaseTypeID;
	};
}

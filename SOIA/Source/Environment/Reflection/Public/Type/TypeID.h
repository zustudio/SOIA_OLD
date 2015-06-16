
#pragma once

//#include "StringParser.h"
//using namespace Environment::Meta;
#include <string>
#include <vector>

#include "TypeName.h"

namespace Environment
{

	class LIBIMPEXP TypeID
	{
	public:
		explicit TypeID(const char* InString);
		explicit TypeID(const std::string& InString);
		template<typename T> static TypeID FromType()
		{
			return TypeID(TYPENAME(T));
		}

		template<typename T>
		constexpr static const char* StaticType()
		{
			return "ABC";
		}
		
		
		bool operator ==(const TypeID& InOther) const;
		operator std::string() const;
		std::string ToString() const;

		//checks:
		bool IsPointer() const;

		//operations:
		TypeID Dereference() const;
		TypeID RemoveSuffix_Base() const;

		//helper function
	protected:
		static std::vector<std::string> MatchPattern(const std::string& InInput, const std::string& InPattern);
		static std::string ParseGCCName( const char* mangled_name );
		static std::string ParseName(const std::string& InName);

	private:
		static std::vector<std::pair<std::string, std::string> > IDNameCache;
		std::string TypeString;
	};
}


#pragma once

//#include "StringParser.h"
//using namespace Environment::Meta;
#include <string>
#include <vector>

#include "TypeName.h"
#include "Atom.h"

namespace Environment
{
	class LIBIMPEXP TypeID : public Atom
	{
	public:
		explicit TypeID(const char* InString);
		explicit TypeID(const std::string& InString);
		template<typename T> static TypeID FromType()
		{
			auto result = TypeID(TYPENAME(T));
			result.bConst = std::is_const<typename std::template remove_reference<T>::type>::value;
			result.bReference = std::is_reference<T>::value;
			return result;
		}

		template<typename T>
		constexpr static const char* StaticType()
		{
			return "ABC";
		}
		
		
		bool operator ==(const TypeID& InOther) const;
		operator std::string() const;
		std::string ToString() const;
		std::string ToEasyString() const;

		//checks:
		bool IsPointer() const;
		bool IsConst() const;
		bool IsReference() const;

		//operations:
		TypeID Decay() const;
		TypeID Dereference() const;
		TypeID RemoveSuffix_Base() const;

		//atom:
		static TypeID FromString(const std::string& InString)
		{
			return TypeID(InString);
		}
		static std::string ToString(const TypeID& InObject)
		{
			return InObject.ToString();
		}

		//helper function
	protected:
		static std::vector<std::string> MatchPattern(const std::string& InInput, const std::string& InPattern);
		static std::string ParseGCCName( const char* mangled_name );
		static std::string ParseName(const std::string& InName);

	private:
		static std::vector<std::pair<std::string, std::string> > IDNameCache;
		std::string TypeString;
		bool bConst;
		bool bReference;
	};
}


#pragma once

//#include "StringParser.h"
using namespace Environment::Meta;
#include <string>
#include <vector>
#include <typeinfo>

namespace Environment
{

	class LIBIMPEXP TypeID
	{
	public:

		CHAR_ARRAY_LITERAL(BracketPattern,_FUNCTION_<#>::RawPointer);
		CHAR_ARRAY_LITERAL(ClassPattern,class )

		explicit TypeID(const std::string& InString);
		template<typename T> static TypeID FromType()
		{
			using BracketPattern = CharArrayToList< CharArray_BracketPattern>;
			using ClassPattern = ConstExprList<char, 'c', 'l', 'a', 's', 's', ' '>;

			using RawList = CharArrayToList<CharArray_FUNCTION_<T> >;
			using Type1 = Replace<RawList, ClassPattern, ConstExprList<char> >;

			using Type2 = Replace<Type1, ConstExprList<char, ' ', '*'>, ConstExprList<char, '*'>>;
			//using Type3 = Replace<RawList, ConstExprList<char, ' ', ','>, ConstExprList<char, ','> >;

			return TypeID(ListToArrayObject<Type2>().Value);
			//return TypeID(ParseName(ParseGCCName((typeid(T).name()))));
		}

		template<typename T>
		constexpr static const char* StaticType()
		{
			return "ABC";
		}
		
		
		bool operator ==(const TypeID& InOther) const;
		operator std::string() const;

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

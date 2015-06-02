
#pragma once

//#include "StringParser.h"
//using namespace Environment::Meta;
#include "CharReplacer.h"
#include <string>
#include <vector>
#include <typeinfo>

namespace Environment
{

	class LIBIMPEXP TypeID
	{
	public:

		template<typename T>
		struct FromType_Helper
		{
			static constexpr const auto input = TypeCharArrayLiteral<T>::Create();
			static constexpr const auto pattern = CharArrayLiteral("class ");
			static constexpr const auto replacement = CharArrayLiteral("");
			static constexpr const auto replacer = CharReplacer<void*, nullptr>(pattern, replacement, input);

			static constexpr const auto input2 = CharArrayLiteral("");
			static constexpr const auto pattern2 = CharArrayLiteral(" ");
			static constexpr const auto replacement2 = CharArrayLiteral("");
			static constexpr const auto replacer2 = CharReplacer<const CharReplacer<void*, nullptr>&, replacer>(pattern2, replacement2, input2);
			
			TypeID Create()
			{
				return TypeID(ReplacerToArray<decltype(replacer2), replacer2>::Get().data());
			}
		};

		explicit TypeID(const char* InString);
		explicit TypeID(const std::string& InString);
		template<typename T> static TypeID FromType()
		{
			return FromType_Helper<T>().Create();
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

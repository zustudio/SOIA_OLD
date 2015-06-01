
#pragma once

//#include "StringParser.h"
//using namespace Environment::Meta;
#include "ConstExprByteParser.h"
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
			using typeT = CharArray_FUNCTION_<T>;
			static constexpr const auto input = literal_str(typeT::Pointer, typeT::Size());
			static constexpr const auto pattern = literal_str("class ");
			static constexpr const auto replacement = literal_str("");
			static constexpr const auto replacer = CharReplacer<void*, nullptr>(pattern, replacement, input);

			
			TypeID Create()
			{
				const auto carr = SetReplacer<decltype(replacer), replacer>::ArrayFromReplacer::get();
				const std::string text = carr.data();
				return TypeID(text);
			}
		};

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

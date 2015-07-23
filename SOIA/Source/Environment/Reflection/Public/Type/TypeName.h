/////////////////////////////////////////////////////////////////////////////////////////////
///	Project:	SOIA
///	Author:		Maxim Urschumzew
/// Year:		2015
///	File:		TypeName.h
/// Purpose:	Provides the macro 'TYPENAME(Type)'. This macro generates a compiler independent
///				formatted string (usable with GCC and MSVC) holding the name of the passed Type.
///				The resulting string is formatted like the unmangled GCC typeid(Type).name() and 
///				is produced with as little runtime overhead as possible.
///				In order to yield better build times on MSVC it is possible to turn off the for-
///				mat conversion via setting
///

#pragma once

#include "Definitions.h"

	struct ParseHelper
	{
		template<typename Type>
		using is_const = typename std::is_const<typename std::template remove_reference<Type>::type>;
		template<typename Type>
		static inline auto AddConst(const std::string& InString) -> typename std::enable_if<is_const<Type>::value, std::string>::type
		{
			return InString + " const";
		}

		template<typename Type>
		static inline auto AddConst(const std::string& InString) -> typename std::enable_if<!is_const<Type>::value, std::string>::type
		{
			return InString;
		}

		template<typename Type>
		static inline auto AddReference(const std::string& InString) -> typename std::enable_if<std::is_reference<Type>::value, std::string>::type
		{
			return InString + " &";
		}

		template<typename Type>
		static inline auto AddReference(const std::string& InString) -> typename std::enable_if<!std::is_reference<Type>::value, std::string>::type
		{
			return InString;
		}
		#define ADD_MODIFIERS(Type,TypeName) \
			ParseHelper::AddReference<Type>(ParseHelper::AddConst<Type>(TypeName))
	};

	#ifdef _MSC_VER

		#include "CharReplacer.h"
		#include "TypeCharArrayLiteral.h"
		using namespace Environment;

		// general definition for all types, converts MSVC-style __FUNCTION__ output into 
		// gcc (typeid) compatible strings
		template<typename T, typename...>
		struct FromType_Helper
		{
			static constexpr const auto input = TypeCharArrayLiteral<T>::Create();
			static constexpr const auto pattern = CharArrayLiteral("class ");
			static constexpr const auto replacement = CharArrayLiteral("");
			static constexpr const auto replacer = CharReplacer<void*, nullptr>(pattern, replacement, input);

			static constexpr const auto input2 = CharArrayLiteral("");
			static constexpr const auto pattern2 = CharArrayLiteral(" *");
			static constexpr const auto replacement2 = CharArrayLiteral("*");
			static constexpr const auto replacer2 = CharReplacer<const CharReplacer<void*, nullptr>&, replacer>(pattern2, replacement2, input2);

			static constexpr const auto input3 = CharArrayLiteral("");
			static constexpr const auto pattern3 = CharArrayLiteral(",");
			static constexpr const auto replacement3 = CharArrayLiteral(", ");
			static constexpr const auto replacer3 = CharReplacer<const CharReplacer<const CharReplacer<void*, nullptr>&, replacer>&, replacer2>(pattern3, replacement3, input3);

			std::string Get()
			{
				#define OFF 0
				#define ON 1

				#if def_BUILD_NONCOMPATIBLE_MSVC_OPTIMIZATION == OFF
					return ReplacerToArray<decltype(replacer3), replacer3>::Get().data();
				#else
					return ADD_MODIFIERS(T,typeid(T).name());
				#endif

				#undef OFF
				#undef ON
			}
		};
		#define TYPENAME(Type) (FromType_Helper<Type>().Get())

	#else

		#include <typeinfo>
		#include <cxxabi.h>
		#include <cstdlib>

		static std::string ParseGCCName(const char* mangled_name)
		{
			int status;
			char* temp = __cxxabiv1::__cxa_demangle(mangled_name, nullptr, nullptr, &status);
			if (temp)
			{
				std::string result(temp);
				std::free(temp);
				return result;
			}
			else return mangled_name;
		}
		#define TYPENAME(Type) (ADD_MODIFIERS(Type,ParseGCCName(typeid(Type).name())))

	#endif

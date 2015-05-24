
#pragma once

#include "ConstExprList.h"

//#include <array>

namespace Environment
{
	namespace Meta
	{
		//////////////////////////////////////////////////////////
		// Strings

		struct CharPointer
		{
			constexpr CharPointer(const char* InPointer) :
				Pointer(InPointer)
			{}
			const char* Pointer;
		};

#define CHAR_ARRAY_LITERAL(num,chararray) \
		struct CharArray_##num\
		{ \
		private: \
			static constexpr const char* RawPointer = #chararray; \
		public: \
			static constexpr const auto Pointer = Environment::Meta::CharPointer(RawPointer); \
			static constexpr const int Size(int Index = 0) { return *(RawPointer + Index) == 0 ? Index : Size(Index + 1); } \
		};

		CHAR_ARRAY_LITERAL(1,<#>);
		CHAR_ARRAY_LITERAL(2,<FOUND>);


		template<class T>
		struct CharArray_FUNCTION_
		{
		private:
			static constexpr const char* RawPointer()
			{
				return __FUNCTION__;
			}
		public:
			static constexpr const auto Pointer = Environment::Meta::CharPointer(RawPointer());
			static constexpr const int Size(int Index = 0) { return *(RawPointer() + Index) == 0 ? Index : Size(Index + 1); }
		};


		template<const CharPointer& p_Chars>
		struct NthChar
		{
			static constexpr const char Do(int index)
			{
				return *(p_Chars.Pointer + index);
			}
		};

		/////////////////////////////////////////////////////
		// create lists
		template<typename CharArray>
		using CharArrayToList = typename typename UsingEveryIndex<CharArray::Size(), Action<ListFromIndices, ActionArgs<char, NthChar<CharArray::Pointer> > > >::Result::Value;

		/////////////////////////////////////////////////////
		// testing automatic indexing


		template<int current, int... indices>
		struct CreateTestList : CreateTestList<current - 1, current, indices...>
		{
		};

		template<int... indices>
		struct CreateTestList<0, indices...>
		{
			using value = ConstExprList<int, indices...>;
		};


	}
}

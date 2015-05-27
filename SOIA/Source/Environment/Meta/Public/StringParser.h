
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

//Environment::CharArray_FUNCTION_<d

		template<class T>
		struct CharArray_FUNCTION_
		{
#ifdef __GNUG__
	#define ACCESSOR_FUNC static constexpr const char* AccessorFunc(const char* InPointer) {return InPointer;}
	#define GET_FULL_NAME AccessorFunc(__PRETTY_FUNCTION__)
	#define START_TO_TYPE 0
	#define TYPE_TO_END 0
#elif _MSC_VER
	#define ACCESSOR_FUNC static constexpr const char* AccessorFunc() {return __FUNCTION__;}
	#define GET_FULL_NAME AccessorFunc()
	#define START_TO_TYPE 0
	#define TYPE_TO_END 0
#endif

		private:
			ACCESSOR_FUNC

		public:
			static constexpr const Environment::Meta::CharPointer Pointer = Environment::Meta::CharPointer(GET_FULL_NAME + START_TO_TYPE);
			static constexpr const int Size(int Index = 0) { return *(Pointer.Pointer + Index) == 0 ? Index - TYPE_TO_END : Size(Index + 1); }
		};


		template<const CharPointer& p_Chars>
		struct NthChar
		{
//			static constexpr const char Do(int index)
//			{
//				return *(p_Chars.Pointer + index);
//			}

			template<int InIndex>
			struct Do
			{
				static constexpr const char Value = *(p_Chars.Pointer + InIndex);
			};
		};

		/////////////////////////////////////////////////////
		// create lists
		template<typename CharArray>
		using CharArrayToList = typename UsingEveryIndex<CharArray::Size(), Action<ListFromIndices, ActionArgs<char, NthChar<CharArray::Pointer> > > >::Value;

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

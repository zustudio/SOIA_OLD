
#pragma once

#include "CharArrayLiteral.h"

namespace Environment
{

	template<class T>
	struct TypeCharArrayLiteral
	{
#ifdef __GNUG__
#define ACCESSOR_FUNC static constexpr const char* AccessorFunc(const char* InPointer) {return InPointer;}
#define GET_FULL_NAME AccessorFunc(__PRETTY_FUNCTION__)
#define START_TO_TYPE 0
#define TYPE_TO_END 0
#elif _MSC_VER
#define ACCESSOR_FUNC static constexpr const char* AccessorFunc() {return __FUNCTION__;}
#define GET_FULL_NAME AccessorFunc()
#define START_TO_TYPE 34
#define TYPE_TO_END 15
#endif

	private:
		ACCESSOR_FUNC
		static constexpr const char* Pointer = GET_FULL_NAME + START_TO_TYPE;
		static constexpr const int Size(int Index = 0) { return *(Pointer + Index) == 0 ? Index - TYPE_TO_END : Size(Index + 1); }

	public:
		static constexpr const CharArrayLiteral Create() { return CharArrayLiteral(Pointer, Size()); }
	};

}
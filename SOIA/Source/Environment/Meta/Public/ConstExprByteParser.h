
#pragma once

#include <array>
//#include "StringParser.h"


namespace Environment
{
	//template<int Size>
	//struct ConstExprIntArray;

	//template<>
	//struct ConstExprIntArray<0>
	//{
	//	constexpr int Get(int n)
	//	{
	//		return 0;
	//	}
	//};

	//template<int Size>
	//struct ConstExprIntArray : public ConstExprIntArray<Size - 1>
	//{
	//	using Next = ConstExprIntArray<Size - 1>;

	//	template<typename InType, typename... TailTypes>
	//	constexpr ConstExprIntArray(InType InValue, TailTypes... TailValues)
	//		:
	//		Value(InValue),
	//		Next(TailValues...)
	//	{}

	//	constexpr const int Get(const int n)
	//	{
	//		return ConstExprIntArray<0>::Get(0);
	//		/*return n == 0 ?
	//			Value :
	//			0;*/
	//		/*return n == 0 ?
	//			Value :
	//			ConstExprIntArray<Size - 1>::Get(0);*/
	//		//return 0;
	//	}

	//	const int Value;
	//};


	struct IntList
	{
		constexpr IntList(int i1, int i2, int i3)
			:
			ii1(i1),
			ii2(i2),
			ii3(i3)
		{}

		constexpr const int Get(int index)
		{
			return index == 0 ?
				ii1 :
				index == 1 ?
					ii2 :
					ii3;
		}

		const int ii1;
		const int ii2;
		const int ii3;
	};
	



	class literal_str
	{
	public:
		const char* const text_ptr;
		unsigned int text_size;
	public:
		template <unsigned int N>
		constexpr literal_str(const char(&aStr)[N]) :
			text_ptr(aStr), text_size(N - 1)
		{
			static_assert(N >= 1, "Invalid string literal! Length is zero!");
			static_assert(N < 255, "String Literal is too long too fit into char!");
		};

		constexpr literal_str(const char* const InPtr, unsigned int InSize)
			:
			text_ptr(InPtr),
			text_size(InSize)
		{}
	};

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
#define START_TO_TYPE 33
#define TYPE_TO_END 15
#endif

	private:
		ACCESSOR_FUNC

	public:
		//static constexpr const Environment::Meta::CharPointer Pointer = Environment::Meta::CharPointer(GET_FULL_NAME + START_TO_TYPE);
		static constexpr const char* Pointer = GET_FULL_NAME + START_TO_TYPE;
		static constexpr const int Size(int Index = 0) { return *(Pointer + Index) == 0 ? Index - TYPE_TO_END : Size(Index + 1); }
	};

	//template<class Indices = typename make_int_range<10>::type>
	//struct lookup_table;
	//template<int...Indices>
	//struct lookup_table<int_pack<Indices...>>
	//{
	//	static const int size = sizeof...(Indices);
	//	typedef std::array<char, size> array_type;
	//	static const array_type& get(const char* InText)
	//	{
	//		static const array_type arr = { { (*(InText + Indices))... } };
	//		return arr;
	//	}
	//};

	////////////////////////////////////////////////////////////////////////////////
	// Byte funcs
	constexpr const int Encode4Bytes(char c0, char c1, char c2, char c3)
	{
#define cx(n) (c##n)
		return (c0 + (c1 << 8) + (c2 << 16) + (c3 << 24));
#undef cx
	}

	constexpr const char Decode4Bytes(int Value, char n)
	{
		return (Value >> n * 8) & 0xFF;
	}


	//////////////////////////////////////////////////////////////////////////////////
	// Replacement
	
	constexpr const int NotZero(int Value)
	{
		return Value < 1 ?
			1 :
			Value;
	}

	template<typename NextReplacerType, NextReplacerType NextReplacer>
	struct CharReplacer
	{
	public:
		constexpr CharReplacer(const literal_str& InPattern, const literal_str& InReplacement, const literal_str& InText/*, const CharReplacer* InNext*/)
			:
			Pattern(InPattern),
			Replacement(InReplacement),
			Input(InText),
			CheckPointDelta(NotZero(GetSize_Input() / 4)),
			Check1(FindNthItem_Worker(CheckPointDelta, -1, -1, -1)),
			Check2(FindNthItemSet_FromCheckPoint(CheckPointDelta * 2, Check1)),
			Check3(FindNthItemSet_FromCheckPoint(CheckPointDelta * 3, Check2)),
			CheckPoints(IntList(Check1, Check2, Check3)),
			Size(GuessSize())
			
			/*,
			NextReplacer(InNext)*/
		{}

		//constexpr const CharReplacer_Base* NextReplacer = InNextReplacer;
		const literal_str& Pattern;
		const literal_str& Replacement;
		const literal_str& Input;
		const int CheckPointDelta;
		const int Check1;
		const int Check2;
		const int Check3;
		const IntList CheckPoints;
		const int Size;


	public:
		

	public:

		constexpr const char IterateUntilNthChar(int TargetIndex)
		{
			return '?';
			//return FindNthItem(TargetIndex, TargetIndex, -1, -1);
		}

		constexpr const char FindNthItem(int ItemNum)
		{
			return Decode4Bytes(FindNthItemSet(ItemNum), 0);
		}
		
		constexpr const int GetCheckNum(int ItemNum)
		{
			return ItemNum / CheckPointDelta - 1;
		}

		constexpr const int FindNthItemSet(int ItemNum)
		{
			return ItemNum < CheckPointDelta?
				FindNthItem_Worker(ItemNum, -1, -1, -1) :
				FindNthItemSet_FromCheckPoint(ItemNum, CheckPoints.Get(GetCheckNum(ItemNum)) /*ItemNum < (CheckPointDelta)?*/ /*Encode4Bytes('N', -1, -1, -1) */ /*Check1*/ );
	
		}

		constexpr const int FindNthItemSet_FromCheckPoint(int ItemNum, int CheckPoint)
		{
#define CheckVal(n)	Decode4Bytes(CheckPoint, n)
			return FindNthItem_Worker(ItemNum, CheckVal(1), CheckVal(2), CheckVal(3));
		}


		constexpr const int FindNthItem_Worker(int ItemNum, int ItemIterator, int i_CurrentListItem, int i_CurrentReplacementItem/*, int i_i_PatternStart*/)
		{
			return ItemIterator == ItemNum ?			// have we arived at our target item?
				(i_CurrentReplacementItem < 0 ?		// are we outside of a replacement?
					Encode4Bytes(GetNthChar_Input(i_CurrentListItem), ItemNum, i_CurrentListItem, i_CurrentReplacementItem) :					// yes: than get current main-list item
					Encode4Bytes(GetNthChar_Replacement(i_CurrentReplacementItem), ItemNum, i_CurrentListItem, i_CurrentReplacementItem)) :		// no: pick item from replacement list


				i_CurrentReplacementItem < 0 ?				// we did not arive at target item: are we inside a replacement?
				(GetMatchLength(i_CurrentListItem + 1) < 0 ?		// no, is the next item a replacement?
					FindNthItem_Worker(ItemNum, ItemIterator + 1, i_CurrentListItem + 1, -1) :	// no: increase simple list
					(Replacement.text_size > 0 ?
						FindNthItem_Worker(ItemNum, ItemIterator + 1, i_CurrentListItem + 1, 0) :		// yes: set replacement list
						FindNthItem_Worker(ItemNum, ItemIterator, i_CurrentListItem + 1, 0))) :
				(i_CurrentReplacementItem + 1 < Replacement.text_size ?	// yes, is the next item our current replacement as well?
					FindNthItem_Worker(ItemNum, ItemIterator + 1, i_CurrentListItem, i_CurrentReplacementItem + 1) :	//yes: increase replacement list
					FindNthItem_Worker(ItemNum, ItemIterator + 1, i_CurrentListItem + GetMatchLength(i_CurrentListItem), (i_CurrentListItem + GetMatchLength(i_CurrentListItem)) - GetNextMatchStart(i_CurrentListItem + GetMatchLength(i_CurrentListItem)))); //no: calculate values for next round

		}

		

		constexpr const int GetNextMatchStart(int InInputIndex)
		{
			return InInputIndex >= GetSize_Input()?
				GetSize_Input() :
				GetMatchLength(InInputIndex, 0) < 0 ?
					GetNextMatchStart(InInputIndex + 1) :
					InInputIndex;
		}

		constexpr const int GetMatchLength(int InInputIndex, int PatternIndex = 0)
		{
			//return -1;
			return PatternIndex == Pattern.text_size ?
				PatternIndex :
				InInputIndex >= GetSize_Input() ?
					-1 :
					GetNthChar_Input(InInputIndex) == GetNthChar_Pattern(PatternIndex) ?
						GetMatchLength(InInputIndex + 1, PatternIndex + 1) :
						-1;
		}


		constexpr const char GetNthChar(int InNum)
		{
			//return 'n';
			return FindNthItem(InNum);
		}

		constexpr const char GetNthChar_Input(int InNum)
		{
			return GetNthChar_Input<NextReplacerType>(InNum);
		}

		template<typename...>
		constexpr const char GetNthChar_Input(int InNum)
		{
			return NextReplacer.GetNthChar(InNum);
		}

		template<>
		constexpr const char GetNthChar_Input<void*>(int InNum)
		{
			return InNum >= Input.text_size?
				0 :
				*(Input.text_ptr + InNum);
		}

		

		constexpr const char GetNthChar_Pattern(int InNum)
		{
			return *(Pattern.text_ptr + InNum);
		}

		constexpr const char GetNthChar_Replacement(int InNum)
		{
			return *(Replacement.text_ptr + InNum);
		}



		constexpr const int GetSize_Input()
		{
			return GetSize_Input<NextReplacerType>();
		}

		template<typename...>
		constexpr const int GetSize_Input()
		{
			return NextReplacer.Size;
		}

		template<>
		constexpr const int GetSize_Input<void*>()
		{
			return Input.text_size;
		}


		
		constexpr const int GuessSize()
		{
			return FindZeroCharGuessing(GetSize_Input());
		}

		constexpr const int FindZeroCharGuessing(int InputIndex)
		{
#define NextInputIndex InputIndex - Pattern.text_size + Replacement.text_size

			return GetNthChar(InputIndex) == 0 && GetNthChar(InputIndex - 1) != 0 ?
				InputIndex :
				FindZeroCharGuessing(NextInputIndex);

#undef NextInputIndex

		}

	};







	template<char InVal>
	struct ConstExprChar
	{
		static constexpr const char Value = InVal;
	};



	/*template<class T> struct id { typedef T type; };
	template<int... SomeI> struct int_pack {};
	template<int N, int...Tail> struct make_int_range
		: make_int_range<N - 1, N - 1, Tail...> {};
	template<int...Tail> struct make_int_range<0, Tail...>
		: id<int_pack<Tail...>>{};

	template<typename CharReplacerType, CharReplacerType& replacer>
	struct SetReplacer
	{
		static constexpr const int ReplacerSize = replacer.Size;
		template<class Indices = typename make_int_range<ReplacerSize>::type>
		struct ReplacerToArray;
		template<int...Indices>
		struct ReplacerToArray<int_pack<Indices...>>
		{
			static const int size = sizeof...(Indices);
			typedef std::array<char, size> array_type;
			static const array_type& get()
			{

				static const array_type arr = { { (ConstExprChar<replacer.GetNthChar(Indices)>::Value)... } };
				return arr;
			}
		};
	};*/


	template<typename InAction, int InCurrentIndex, int... InTailIndices>
	struct UsingEveryIndex_Helper : UsingEveryIndex_Helper<InAction, InCurrentIndex - 1, InCurrentIndex - 1, InTailIndices...>
	{};

	template<typename InAction, int... InTailIndices>
	struct UsingEveryIndex_Helper<InAction, 0, InTailIndices...>
	{
		using Result = typename InAction::template Inner<InTailIndices...>;
	};

	template<int MaxIndex, typename InAction>
	using UsingEveryIndex = typename UsingEveryIndex_Helper<InAction, MaxIndex>::Result;


	template<typename CharReplacerType, CharReplacerType& replacer>
	struct SetReplacer
	{
		static constexpr const int ReplacerSize = replacer.Size;

		

		struct FromReplacerHelper
		{
			template<int...Indices>
			struct Inner
			{
				static const int size = sizeof...(Indices);
				typedef std::array<char, size + 1> array_type;
				static const array_type& get()
				{

					static const array_type arr = { { (ConstExprChar<replacer.GetNthChar(Indices)>::Value)..., 0 } };
					return arr;
				}
			};
		};

		using ArrayFromReplacer = typename UsingEveryIndex<ReplacerSize, FromReplacerHelper>;
	};

}
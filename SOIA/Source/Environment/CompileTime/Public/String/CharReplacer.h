
#pragma once

#include "ConstExprChar.h"
#include "CharArrayLiteral.h"
#include "TypeCharArrayLiteral.h"
#include "IndexPack.h"
#include "Vector4Int.h"
#include "IntExpressions.h"


namespace Environment
{

	//////////////////////////////////////////////////////////////////////////////////
	// Replacement
	

	template<typename NextReplacerType, NextReplacerType NextReplacer>
	struct CharReplacer
	{
	private:
		const CharArrayLiteral& Pattern;
		const CharArrayLiteral& Replacement;
		const CharArrayLiteral& Input;
		const int CheckPointDelta;
		const int Check0;
		const int Check1;
		const int Check2;
		const int Check3;
		const Vector4Int CheckPoints;
	public:
		const int Size;

	public:
		constexpr CharReplacer(const CharArrayLiteral& InPattern, const CharArrayLiteral& InReplacement, const CharArrayLiteral& InText/*, const CharReplacer* InNext*/)
			:
			Pattern(InPattern),
			Replacement(InReplacement),
			Input(InText),
			CheckPointDelta(NotZero(GetSize_Input() / 4)),
			Check0(FindNthItem_Worker(0, -1, -1, -1)),
			Check1(FindNthItemSet_FromCheckPoint(CheckPointDelta * 1, Check0)),
			Check2(FindNthItemSet_FromCheckPoint(CheckPointDelta * 2, Check1)),
			Check3(FindNthItemSet_FromCheckPoint(CheckPointDelta * 3, Check2)),
			CheckPoints(Vector4Int(Check0, Check1, Check2, Check3)),
			Size(GuessSize())
		{}

		constexpr const char GetNthChar(int ItemNum)
		{
			return Decode4Bytes(FindNthItemSet(ItemNum), 0);
		}

		constexpr const int FindNthItemSet(int ItemNum)
		{
			return FindNthItemSet_FromCheckPoint(ItemNum, CheckPoints.Get(ItemNum / CheckPointDelta) );
		}

		constexpr const int FindNthItemSet_FromCheckPoint(int ItemNum, int CheckPoint)
		{
#define CheckVal(n)	Decode4Bytes(CheckPoint, n)
			return FindNthItem_Worker(ItemNum, CheckVal(1), CheckVal(2), CheckVal(3));
#undef CheckVal
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
			return PatternIndex == Pattern.text_size ?
				PatternIndex :
				InInputIndex >= GetSize_Input() ?
					-1 :
					GetNthChar_Input(InInputIndex) == GetNthChar_Pattern(PatternIndex) ?
						GetMatchLength(InInputIndex + 1, PatternIndex + 1) :
						-1;
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


	/////////////////////////////////////////////////////////////////////////////////
	// Array Generation
	template<typename CharReplacerType, CharReplacerType& replacer>
	struct ReplacerToArray_Helper
	{
		static constexpr const int ReplacerSize = replacer.Size;

		struct IndexPackReceiver
		{
			template<int...Indices>
			struct Inner
			{
				static const int size = sizeof...(Indices);
				typedef std::array<char, size + 1> array_type;
				static const array_type& Get()
				{
					static const array_type arr = { { (ConstExprChar<replacer.GetNthChar(Indices)>::Value)..., 0 } };
					return arr;
				}
			};
		};

		using Result = typename UsingEveryIndex<ReplacerSize, IndexPackReceiver>;
	};

	template<typename CharReplacerType, CharReplacerType& replacer>
	using ReplacerToArray = typename ReplacerToArray_Helper<CharReplacerType, replacer>::Result;
}
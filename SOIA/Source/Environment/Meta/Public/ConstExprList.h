#pragma once

namespace Environment
{
	namespace Meta
	{

		struct PatternPosition
		{
			constexpr PatternPosition(int InBegin, int InSize) :
				Begin(InBegin),
				Size(InSize),
				End(InBegin + InSize)
			{}
			const int Begin;
			const int Size;
			const int End;
		};




		template<typename Type, Type... Items>
		struct ConstExprListItem;

		template<typename Type>
		struct ConstExprListItem<Type>
		{
			static const constexpr Type Get(int InIndex)
			{
				return (Type)0;
			}

			template<int InIndex>
			static const constexpr Type Get()
			{
				return (Type)0;
			}
		};

		template<typename Type, Type InItem, Type...TailItems>
		struct ConstExprListItem<Type, InItem, TailItems...>
		{
			using Next = ConstExprListItem<Type, TailItems...>;

			static const constexpr Type Item = InItem;

			static const constexpr Type Get(int InIndex)
			{
				return InIndex == 0 ? Item : Next::Get(InIndex - 1);
			}

			template<int InIndex>
			static const constexpr Type Get()
			{
				return Next::Get<InIndex - 1>();
			}

			template<>
			static const constexpr Type Get<0>()
			{
				return Item;
			}
		};

		template<typename Type, Type... Items>
		struct ConstExprList
		{
			using List = ConstExprList<Type, Items...>;
			using RawList = ConstExprListItem<Type, Items...>;
			using ValueType = Type;

			static constexpr const int Size = sizeof...(Items);

			constexpr ConstExprList() {}

			template<int InIndex>
			static const constexpr Type Get()
			{
				return RawList::Get<InIndex>();
			}

			static const constexpr Type Get(int InIndex)
			{
				return RawList::Get(InIndex);
			}

			template<int Offset>
			struct GetOperation
			{
				static constexpr const Type Do(int InIndex)
				{
					return Get(InIndex + Offset);
				}
			};


			template<typename InQuest>
			struct MatchPattern
			{
				////////////////////////////////////////////////////
				// Parameter
				using Quest = typename InQuest;

				// check whether types of lists match
				static_assert(std::is_same<typename List::ValueType, typename Quest::ValueType>::value, "ERROR: FindMatch is being instantiated with lists with different value types!");

				////////////////////////////////////////////////////
				// Functions

				/// counting

				//template<int Offset, int Index, int...Indices>
				static const constexpr int Count(int Index = 0)
				{
					return Index == List::Size ?
						0 :
						FindWord(Index).Begin == List::Size ?
						0 :
						1 + Count(FindWord(Index).End);
				}

				static const constexpr int CommulatedPatternSize(int Index = Count() - 1)
				{
					return Index == -1 ?
						0 :
						FindNthWord(Index).Size + CommulatedPatternSize(Index - 1);
				}

				/// finding

				struct NthWordToList
				{
					static const constexpr int Do(int WordNum)
					{
						return WordNum % 2 == 0 ?
							FindNthWord(WordNum / 2).Begin :
							FindNthWord((WordNum - 1) / 2).Size;
					}
				};

				static const constexpr PatternPosition FindNthWord(int WordNum, int Index = 0)
				{
#define NULLWORD PatternPosition(List::Size, -1)

					return Index == List::Size ?
						NULLWORD :
						FindWord(Index).Begin == List::Size ?
							NULLWORD :
							WordNum == 0 ?
								FindWord(Index) :
								FindNthWord(WordNum - 1, FindWord(Index).End);
				}

				static const constexpr PatternPosition FindWord(int Index = 0)
				{
#define START FindStart(Index)
#define END FullMatch(START, 0)

					return Index == List::Size ?
						PatternPosition(List::Size, -1) :
						END > -1 ?
							PatternPosition(START, END - START) :
							FindWord(Index + 1);

#undef START
#undef END
				}


				static constexpr const ValueType WildCardItem = '*';
				static constexpr const ValueType ContWildCardItem = '#';

				//returns (index of last element + 1) if matched, -1 otherwise
				static const constexpr int FullMatch(int ListIndex, int QuestIndex)
				{
#define QuestItem Quest::Get(QuestIndex)

					return QuestIndex == Quest::Size ?
						ListIndex :
						QuestItem == WildCardItem?
							FullMatch(ListIndex + 1, QuestIndex + 1) :
							QuestItem == ContWildCardItem?
								(FullMatch(ListIndex + 1, QuestIndex + 1) >= 0?
									FullMatch(ListIndex + 1, QuestIndex + 1) :
									FullMatch(ListIndex + 1, QuestIndex)) :
								ItemsEqual(ListIndex, QuestIndex) ?
									FullMatch(ListIndex + 1, QuestIndex + 1) :
									-1;

#undef QuestItem
				}

				static const constexpr int FindStart(int Index)
				{
					return Index == List::Size ?
						Index :
						ItemsEqual(Index, 0) || Quest::Get(0)==WildCardItem || Quest::Get(0)==ContWildCardItem?
							Index :
							FindStart(Index + 1);
				}

				//----- helpers -----
				static const constexpr int ItemsEqual(int ListIndex, int QuestIndex)
				{
					return List::Get(ListIndex) == Quest::Get(QuestIndex) ? true : false;
				};


			};
		};

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// matching patterns in char lists
		struct ReplaceAction
		{
			template<typename Args, int... InIndices>
			struct Inner
			{
				using List = typename Args::Get;
				using ReplacementList = typename typename Args::Next::Get;
				using PatternList = typename typename typename Args::Next::Next::Get;

				using Type = typename List::ValueType;


				static constexpr Type GetNthItem(int ItemNum)
				{
					return FindNthItem(ItemNum, -1, -1, -1, 0);
				}

				static constexpr Type FindNthItem(int ItemNum, int ItemIterator, int i_CurrentListItem, int i_CurrentReplacementItem, int i_i_PatternStart)
				{
#define PatternListGet(index)	(index < PatternList::Size? PatternList::Get(index) : List::Size)

#define i_PatternStart			PatternListGet(i_i_PatternStart)
#define di_PatternSize			(PatternList::Get(i_i_PatternStart + 1))
#define i_NextPatternStart		PatternListGet(i_i_PatternStart + 2)

					return ItemIterator == ItemNum ?			// have we arived at our target item?
						(i_CurrentReplacementItem < 0 ?		// are we outside of a replacement?
							List::Get(i_CurrentListItem) :					// if yes, than get current main-list item
							ReplacementList::Get(i_CurrentReplacementItem)) :		// else pick item from replacement list

						i_CurrentReplacementItem < 0 ?				// we did not arive at target item: are we inside a replacement?
							(i_CurrentListItem + 1 < i_PatternStart ?		// no, is the next item a replacement?
								FindNthItem(ItemNum, ItemIterator + 1, i_CurrentListItem + 1, -1, i_i_PatternStart) :	// no: increase simple list
								FindNthItem(ItemNum, ItemIterator + 1, i_CurrentListItem + 1, 0, i_i_PatternStart)) :		// yes: set replacement list
							(i_CurrentReplacementItem + 1 < ReplacementList::Size ?	// yes, is the next item our current replacement as well?
								FindNthItem(ItemNum, ItemIterator + 1, i_CurrentListItem, i_CurrentReplacementItem + 1, i_i_PatternStart) :	//yes: increase replacement list
								FindNthItem(ItemNum, ItemIterator + 1, i_CurrentListItem + di_PatternSize, (i_CurrentListItem + di_PatternSize) - i_NextPatternStart, i_i_PatternStart + 2)); //no: calculate values for next round

#undef i_PatternStart
#undef di_PatternSize
#undef i_NextPatternStart
				}

				
				using Result = ConstExprList<Type, (GetNthItem(InIndices))...>;
			};
		};



		///////////////////////////////////////////////////////
		// index helpers

		template<typename Arg, typename... TailArgs>
		struct ActionArgs : ActionArgs<TailArgs...>
		{
			using Get = Arg;
			using Next = ActionArgs<TailArgs...>;
		};

		template<typename Arg>
		struct ActionArgs<Arg>
		{
			using Get = Arg;
		};

		template<typename ActionStruct, typename ActionArgs>
		struct Action
		{
			using Struct = ActionStruct;
			using Args = ActionArgs;
		};

		template<typename InAction, int InCurrentIndex, int... InTailIndices>
		struct UsingEveryIndex_Inner : UsingEveryIndex_Inner<InAction, InCurrentIndex - 1, InCurrentIndex - 1, InTailIndices...>
		{};

		template<typename InAction, int... InTailIndices>
		struct UsingEveryIndex_Inner<InAction, 0, InTailIndices...>
		{
			using Result = typename InAction::Struct::template Inner<typename InAction::Args, InTailIndices...>;
		};

		template<int MaxIndex, typename InAction>
		struct UsingEveryIndex : UsingEveryIndex_Inner<InAction, MaxIndex>
		{};



		/////////////////////////////////////////////////////////////////////////
		// other type interface

		struct ListFromIndices
		{
			template<typename Args, int... Indices>
			struct Inner
			{
				using Type = typename Args::Get;
				using Operation = typename typename Args::Next::Get;

				using Value = ConstExprList<Type, (Operation::Do(Indices))...>;
			};
		};

		struct CreateArray
		{
			template<typename Args, int... indices>
			struct Inner
			{
				using List = typename Args::Get;
				const typename List::ValueType Value[List::Size + 1] = { (List::Get<indices>())..., 0 };
			};
		};

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		// Access helpers

		template<typename List>
		struct ListToArrayObject_Helper : UsingEveryIndex<List::Size, Action<CreateArray, ActionArgs<List> > > {};

		template<typename List>
		using ListToArrayObject = typename ListToArrayObject_Helper<List>::Result;

		template<typename MatchResult>
		using MatchResultToList = typename typename UsingEveryIndex<MatchResult::Count() * 2, Action<ListFromIndices, ActionArgs<int, typename MatchResult::NthWordToList> > >::Result::Value;

		template<typename List, typename Pattern>
		struct Match_Helper
		{
		private:
			using MatchResult = typename List::template MatchPattern<Pattern>;
		public:
			using PatternMatches = MatchResultToList<MatchResult>;
		};

		template<typename List, typename Pattern, typename Replacement>
		struct Replace_Helper : Match_Helper<List, Pattern>
		{
			using Result = typename typename UsingEveryIndex<List::Size - MatchResult::CommulatedPatternSize() + PatternMatches::Size / 2 * (Replacement::Size), Action<ReplaceAction, ActionArgs<List, Replacement, PatternMatches> > >::Result::Result;
		};

		template<typename List, typename Pattern, typename Replacement>
		using Replace = typename Replace_Helper<List, Pattern, Replacement>::Result;

		template<typename List, int Start, int Size>
		using Sublist = typename typename UsingEveryIndex<Size, Action<ListFromIndices, ActionArgs<typename List::ValueType, typename List::template GetOperation<Start> > > >::Result::Value;

		template<typename List, typename Pattern, int Index>
		struct MatchingSublist_Helper : Match_Helper<List, Pattern>
		{
			using Result = Sublist<List, PatternMatches::Get(Index * 2), PatternMatches::Get(Index * 2 + 1)>;
		};

		template<typename List, typename Pattern, int Index>
		using MatchingSublist = typename MatchingSublist_Helper<List, Pattern, Index>::Result;
	}
}
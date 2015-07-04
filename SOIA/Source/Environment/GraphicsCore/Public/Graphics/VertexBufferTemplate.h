
#pragma once

#include "VertexBuffer.h"

#include "IndexPack.h"
#include "MultipleOperandMathematics.h"

#include <tuple>

namespace Environment
{
	

	template<typename... DataUnravelerTypes>
	class VertexBufferTemplate : public VertexBuffer
	{
		using TupleType = std::tuple<typename DataUnravelerTypes::CompoundDataType...>;

		struct CopyCompoundTypes
		{
			template<int... Indices>
			struct Inner
			{
				static void Execute(typename std::vector<float>::iterator& InFrontIterator, typename std::vector<TupleType>::iterator& InBackIterator)
				{
					bool result[] = { DataUnravelerTypes::UnravelToVector(std::get<Indices>(*InBackIterator), InFrontIterator)... };
				}
			};
		};

	public:
		////////////////////////////////////////////////////////////////////////
		// Functions

		//----- ctor -----
		VertexBufferTemplate()
			:
			BackBuffer()
		{
		}

		//----- public actions -----
		void Add(const typename DataUnravelerTypes::CompoundDataType&... InCompounds)
		{
			BackBuffer.push_back(TupleType(InCompounds...));
		}

		virtual bool VertexBufferTemplate::SwitchBuffers() override
		{
			auto frontIter = FrontBuffer.begin();
			for (auto backIter = BackBuffer.begin(); backIter != BackBuffer.end(); backIter++)
			{
				UsingEveryIndex<sizeof...(DataUnravelerTypes), CopyCompoundTypes>::Execute(frontIter, backIter);
			}
			return true;
		}

		virtual VertexBufferVariable CreateVariable(int InIndex, const std::string& InName)
		{
			VertexBufferVariable result;
			result.Buffer = this;
			result.Name = InName;
			
			int i;
			result.Offset = 0;
			for (i = 0; i < InIndex; i++)
			{
				result.Offset += CompoundSizes[i];
			}
			result.Size = CompoundSizes[i];
			return result;
		}

		//----- helpers -----
		virtual size_t GetRawSize() override
		{
			return BackBuffer.size() * EntrySize;
		}

		virtual size_t GetEntrySize() override
		{
			return EntrySize;
		}

		////////////////////////////////////////////////////////////////
		// Variables
		size_t CompoundSizes[sizeof...(DataUnravelerTypes)] = { DataUnravelerTypes::RawDataSize... };

		//----- constants -----
		static constexpr const size_t EntrySize = CompileTime::Add(DataUnravelerTypes::RawDataSize...);

		//----- backbuffer -----
		std::vector<TupleType> BackBuffer;
	};
}
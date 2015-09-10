
#pragma once

#include "VertexBuffer.h"

#include "IndexPack.h"
#include "MultipleOperandMathematics.h"

#include <tuple>

namespace Environment
{
	
	template<typename RawType, typename... DataUnravelerTypes>
	class VertexBufferTemplate : public VertexBuffer
	{
	public:
		using TupleType = std::tuple<typename DataUnravelerTypes::CompoundDataType...>;

	protected:
		struct CopyCompoundTypes
		{
			template<int... Indices>
			struct Inner
			{
				static void Execute(typename std::vector<RawType>::iterator& InFrontIterator, typename std::vector<TupleType>::iterator& InBackIterator)
				{
					bool result[] = { DataUnravelerTypes::UnravelToVector(std::get<Indices>(*InBackIterator), InFrontIterator)... };
				}
			};
		};

	public:
		////////////////////////////////////////////////////////////////////////
		// Functions

		//----- ctor -----
		VertexBufferTemplate(VertexBufferType InBufferType, BufferContentType InContentType)
			: VertexBuffer(InBufferType, InContentType),
			FrontBuffer(),
			BackBuffer()
		{
		}

		//----- public actions -----
		void Add(const typename DataUnravelerTypes::CompoundDataType&... InCompounds)
		{
			Add(TupleType(InCompounds...));
		}

		void Add(TupleType const & InTupleObject)
		{
			BackBuffer.push_back(InTupleObject);
			RequestBufferUpdate();
		}

		void AddEmpty(int Num)
		{
			for (int i = 0; i < Num; ++i)
			{
				Add(TupleType());
			}
		}

		void Set(int Num, const typename DataUnravelerTypes::CompoundDataType&... InCompounds)
		{
			Set(Num, TupleType(InCompounds...));
		}

		void Set(int Num, TupleType const & InTupleObject)
		{
			BackBuffer[Num] = InTupleObject;
			RequestBufferUpdate();
		}

		virtual void EraseRange(Range<int> InRange) override
		{
			BackBuffer.erase(BackBuffer.begin() + InRange.Lower, BackBuffer.begin() + InRange.Upper);
			RequestBufferUpdate();
		}
		

		bool VertexBuffer::ResizeFrontBuffer()
		{
			FrontBuffer.resize(GetRawSize());
			return true;
		}

		virtual void VertexBufferTemplate::BindBuffer() override
		{
			glBindBuffer(GLBufferType, GLBuffer);
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

		bool VertexBuffer::LoadGLBuffer()
		{
			glBufferData(GLBufferType, FrontBuffer.size() * sizeof(RawType), FrontBuffer.data(), GL_STATIC_DRAW);
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
		virtual size_t GetEntryNum() override
		{
			return BackBuffer.size();
		}
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

		//----- buffer -----
		std::vector<RawType> FrontBuffer;
		std::vector<TupleType> BackBuffer;
	};
}
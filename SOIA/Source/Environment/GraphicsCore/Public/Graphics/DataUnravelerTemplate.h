
#pragma once

#include <vector>

namespace Environment
{
	template<typename InCompoundDataType, typename RawDataType, RawDataType InCompoundDataType:: *... RawDataPointers>
	class DataUnravelerTemplate
	{
	private:
		using RawIteratorType = typename std::vector<RawDataType>::iterator;

	public:
		using CompoundDataType = InCompoundDataType;

		static bool UnravelToVector(const InCompoundDataType& InCompoundData, RawIteratorType& InOutDestination)
		{
			RawDataType NewData[] = { (InCompoundData.*RawDataPointers)... };
			std::copy(NewData, NewData + sizeof...(RawDataPointers), InOutDestination);
			InOutDestination += sizeof...(RawDataPointers);
			return true;
		}

		static constexpr const size_t RawDataSize = sizeof...(RawDataPointers);
	};
}
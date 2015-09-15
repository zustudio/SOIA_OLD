
#pragma once

#include <chrono>

namespace Environment
{
	template<typename DataType>
	class InterpolationFunction
	{
	public:
		using DurationType = std::chrono::duration<float>;

	public:
		virtual bool Interpolate(DataType const & InStart, DataType & InOutCurrent, DataType const & InTarget, DurationType const & TimePassed) = 0;
	};
}
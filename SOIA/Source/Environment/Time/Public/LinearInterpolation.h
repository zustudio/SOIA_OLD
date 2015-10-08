
#pragma once

#include "InterpolationFunction.h"

#include <iostream>

namespace Environment
{
	template<typename DataType>
	class LinearInterpolation : public InterpolationFunction<DataType>
	{
	public:
		using DurationType = InterpolationFunction<DataType>::DurationType;

	public:
		LinearInterpolation(DurationType const & InWholeDuration)
			: InterpolationFunction<DataType>(InWholeDuration)
		{}

	protected:
		virtual float Calculate(float InX) override
		{
			return InX;
		}
	};
}
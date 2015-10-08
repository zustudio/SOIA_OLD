
#pragma once

#include "InterpolationFunction.h"

#include <iostream>
#include <chrono>

namespace Environment
{
	template<typename DataType>
	class InstantInterpolation : public InterpolationFunction<DataType>
	{
	public:
		using DurationType = InterpolationFunction<DataType>::DurationType;

	public:
		InstantInterpolation()
			: InterpolationFunction<DataType>(DurationType(0))
		{}

	protected:
		virtual float Calculate(float InX) override
		{
			return 1;
		}
	};
}

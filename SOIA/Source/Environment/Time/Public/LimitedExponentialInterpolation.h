
#pragma once

#include "InterpolationFunction.h"

#include <iostream>
#include <cmath>

namespace Environment
{
	template<typename DataType>
	class LimitedExponentialInterpolation : public InterpolationFunction<DataType>
	{
	public:
		using DurationType = typename InterpolationFunction<DataType>::DurationType;

	public:
		LimitedExponentialInterpolation(DurationType const & InWholeDuration, double InBase = 2.7182818)
			:
			InterpolationFunction<DataType>(InWholeDuration),
			Base(InBase),
			TimeFactor(Log(InBase, 0.01))
		{}

		/*virtual bool Interpolate(DataType & InOutCurrent, DurationType const & TimePassed) override
		{
			bool interpolating = true;
			float t = TimePassed / WholeDuration;
			auto factor = 1.0 - std::pow(Base, TimeFactor * t);
			if (factor >= 0.99)
			{
				factor = 1;
				interpolating = false;
			}
			InOutCurrent = Start + (End - Start) * factor;

			return interpolating;
		}*/

		virtual float Calculate(float InX) override
		{
			float factor = 1.0 - std::pow(Base, TimeFactor * InX);
			if (factor >= 0.99)
			{
				factor = 1;
			}
			return factor;
		}

		static double Log(double base, double exponent)
		{
			return std::log(exponent) / std::log(base);
		}

	private:
		double Base;
		double TimeFactor;
	};
}

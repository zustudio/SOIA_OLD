
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
		using DurationType = InterpolationFunction<DataType>::DurationType;

	public:
		LimitedExponentialInterpolation(DurationType const & InWholeDuration, double InBase = 2.7182818)
			:
			WholeDuration(InWholeDuration),
			Base(InBase),
			TimeFactor(Log(InBase, 0.01))
		{}

		virtual bool Interpolate(DataType const & InStart, DataType & InOutCurrent, DataType const & InTarget, DurationType const & TimePassed)
		{
			bool interpolating = true;
			float t = TimePassed / WholeDuration;
			auto factor = 1.0 - std::pow(Base, TimeFactor * t);
			if (factor >= 0.99)
			{
				factor = 1;
				interpolating = false;
			}
			InOutCurrent = InStart + (InTarget - InStart) * factor;

			return interpolating;
		}

		static double Log(double base, double exponent)
		{
			return std::log(exponent) / std::log(base);
		}

	private:
		DurationType WholeDuration;
		double Base;
		double TimeFactor;
	};
}
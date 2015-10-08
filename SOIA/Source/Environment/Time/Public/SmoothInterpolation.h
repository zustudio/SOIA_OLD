
#pragma once

#include "InterpolationFunction.h"

#include <iostream>
#include <cmath>

namespace Environment
{
	template<typename DataType>
	class SmoothInterpolation : public InterpolationFunction<DataType>
	{
	public:
		using DurationType = InterpolationFunction<DataType>::DurationType;

	public:
		SmoothInterpolation(DurationType const & InWholeDuration)
			: InterpolationFunction<DataType>(InWholeDuration),
			CurrentVelocity(0)
		{}

		virtual void SetTarget(DataType InTarget) override
		{
			InterpolationFunction<DataType>::SetTarget(InTarget);
			StartVelocity = CurrentVelocity;
			std::cout << "start velocity: " << StartVelocity << std::endl;
		}

	protected:
		float Calculate(float X) override
		{
			using std::powf;
			float const & v = StartVelocity;

			float result = (6.0 - 3.0*v)*powf(X, 5) + (-15.0 + 8.0*v)*powf(X, 4) + (10.0 - 6.0*v)*powf(X, 3) + v*X;
			CurrentVelocity = (30.0 - 15.0*v)*powf(X, 4) + (-60.0 + 32.0*v)*powf(X, 3) + (30.0 - 18.0*v)*powf(X, 2) + v;

			return result;
		}

	private:
		float StartVelocity;
		float CurrentVelocity;
	};
}

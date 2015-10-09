
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
			: InterpolationFunction<DataType>(InWholeDuration)
		{}

		virtual void SetTarget(DataType InTarget) override
		{
			float percentagePassed = TimePassed();
			StartVelocity = CalculateVelocity(percentagePassed);

			InterpolationFunction<DataType>::SetTarget(InTarget);
			//std::cout << "target:" << std::string(InTarget) << "start velocity: " << StartVelocity << std::endl;
		}

	protected:
		float Calculate(float X) override
		{
			using std::powf;
			float const & v = StartVelocity;

			float value = (6.0 - 3.0*v)*powf(X, 5) + (-15.0 + 8.0*v)*powf(X, 4) + (10.0 - 6.0*v)*powf(X, 3) + v*X;
			float velocity = CalculateVelocity(X);

			//std::cout << "f(" << X << ") = " << value << ";  f' = " << velocity << std::endl;
			return value;
		}

		float CalculateVelocity(float X)
		{
			using std::powf;
			float const & v = StartVelocity;
			return (30.0 - 15.0*v)*powf(X, 4) + (-60.0 + 32.0*v)*powf(X, 3) + (30.0 - 18.0*v)*powf(X, 2) + v;
		}

	private:
		float StartVelocity;
	};
}

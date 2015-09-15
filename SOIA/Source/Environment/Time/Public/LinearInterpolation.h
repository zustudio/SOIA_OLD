
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
			: WholeDuration(InWholeDuration)
		{}

		virtual bool Interpolate(DataType const & InStart, DataType & InOutCurrent, DataType const & InTarget, DurationType const & TimePassed)
		{
			bool interpolating = true;
			auto percentagePassed = TimePassed / WholeDuration;
			if (percentagePassed >= 1)
			{
				percentagePassed = 1;
				interpolating = false;
			}
			InOutCurrent = InStart + (InTarget - InStart) * percentagePassed;

			return interpolating;
		}

	private:
		DurationType WholeDuration;
	};
}
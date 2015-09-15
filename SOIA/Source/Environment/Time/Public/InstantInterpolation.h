
#pragma once

#include "InterpolationFunction.h"

namespace Environment
{
	template<typename DataType>
	class InstantInterpolation : public InterpolationFunction<DataType>
	{
	public:
		using DurationType = InterpolationFunction<DataType>::DurationType;

	public:
		InstantInterpolation(DurationType const & InWholeDuration)
			: WholeDuration(InWholeDuration)
		{}

		virtual bool Interpolate(DataType const & InStart, DataType & InOutCurrent, DataType const & InTarget, DurationType const & TimePassed) override
		{
			InOutCurrent = InTarget;
			bool interpolating = TimePassed < WholeDuration;
			return interpolating;
		}

	private:
		DurationType WholeDuration;
	};
}
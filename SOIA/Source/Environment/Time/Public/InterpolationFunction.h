
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
		InterpolationFunction(DurationType const & InWholeDuration)
			:
			WholeDuration(InWholeDuration)
		{}

		virtual void SetTarget(DataType InTarget)
		{
			Start = Current;
			End = InTarget;
		}
		void SetCurrent(DataType InCurrent)
		{
			Start = InCurrent;
			Current = InCurrent;
			End = InCurrent;
		}
		virtual bool Interpolate(DurationType const & TimePassed)
		{
			bool interpolating = true;
			float percentagePassed = TimePassed / WholeDuration;
			if (percentagePassed >= 1)
			{
				percentagePassed = 1;
				interpolating = false;
			}
			Current = Start + (End - Start) * Calculate(percentagePassed);
			return interpolating;
		}

		DataType const & GetTarget()
		{
			return End;
		}
		DataType const & GetCurrent()
		{
			return Current;
		}

	protected:
		virtual float Calculate(float InX) = 0;

	protected:
		DataType Start, Current, End;
		DurationType WholeDuration;
	};
}
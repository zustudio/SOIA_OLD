
#pragma once

#include <chrono>

namespace Environment
{
	template<typename DataType>
	class InterpolationFunction
	{
	public:
		using TimeType = std::chrono::system_clock::time_point;
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
			InterpolationStarted = std::chrono::system_clock::now();
		}
		void SetCurrent(DataType InCurrent)
		{
			Start = InCurrent;
			Current = InCurrent;
			End = InCurrent;
		}
		virtual bool Interpolate()
		{
			bool interpolating = true;
			float percentagePassed = TimePassed();
			if (percentagePassed == 1)
			{
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
		float TimePassed()
		{
			auto TimePassed = std::chrono::duration_cast<DurationType>(std::chrono::system_clock::now() - InterpolationStarted);
			auto percentage = TimePassed / WholeDuration;

			if (percentage >= 1)
			{
				percentage = 1;
			}
			return percentage;
		}

		virtual float Calculate(float InX) = 0;

	protected:
		DataType Start, Current, End;
		DurationType WholeDuration;
		TimeType InterpolationStarted;
	};
}

#pragma once

#include "InterpolationFunction.h"

namespace Environment
{
	template<typename DataType>
	class Interpolator
	{
	private:
		using TimeType = std::chrono::steady_clock::time_point;

	public:
		//----- ctor -----
		/*template<typename... ArgTypes>
		Interpolator(InterpolationFunction<DataType>* InInterpolation, const ArgTypes... & InArguments)
			: Data(InArguments),
			Interpolation(InInterpolation)
		{}*/

		Interpolator(DataType const & InData, InterpolationFunction<DataType>* InInterpolation = nullptr)
			:
			Interpolation(InInterpolation),
			Start(InData),
			Current(InData),
			Target(InData),
			bInterpolating(false)
		{}

		//----- getter -----
		DataType const & operator*() const
		{
			return Current;
		}

		DataType const & operator->() const
		{
			return Current;
		}
		operator DataType() const
		{
			return Current;
		}
		bool operator==(DataType const & InOther) const
		{
			return InOther == Target;
		}
		bool IsInterpolating() const
		{
			return bInterpolating;
		}

		//----- setter -----
		Interpolator<DataType>& operator=(DataType const & InTarget)
		{
			if (Interpolation)
			{
				Start = Current;
				Target = InTarget;
				InterpolationStarted = std::chrono::steady_clock::now();
				bInterpolating = true;
			}
			else
			{
				Current = InTarget;
			}

			return *this;
		}

		//----- interpolation -----
		void Update()
		{
			if (Interpolation && bInterpolating)
			{
				TimeType Now = std::chrono::steady_clock::now();
				bInterpolating = Interpolation->Interpolate(Start, Current, Target, std::chrono::duration_cast<std::chrono::duration<float>>(Now - InterpolationStarted));
			}
		}

	private:

		InterpolationFunction<DataType>* Interpolation;
		DataType Start;
		DataType Current;
		DataType Target;
		TimeType InterpolationStarted;
		bool bInterpolating;
	};
}
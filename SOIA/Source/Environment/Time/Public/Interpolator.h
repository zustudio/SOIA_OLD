
#pragma once

#include "InterpolationFunction.h"

#include "InstantInterpolation.h"

#include <iostream>

namespace Environment
{
	template<typename DataType>
	class Interpolator
	{
	private:
		using TimeType = std::chrono::system_clock::time_point;

	public:
		//----- ctor -----
		/*template<typename... ArgTypes>
		Interpolator(InterpolationFunction<DataType>* InInterpolation, const ArgTypes... & InArguments)
			: Data(InArguments),
			Interpolation(InInterpolation)
		{}*/

		Interpolator(DataType const & InData, InterpolationFunction<DataType>* InInterpolation = nullptr)
			:
			Interpolation(InInterpolation != nullptr ? InInterpolation : new InstantInterpolation<DataType>()),
			bInterpolating(false)
		{}

		//----- getter -----
		DataType const & Get() const
		{
			return Interpolation->GetCurrent();
		}
		DataType const & GetTarget() const
		{
			return Interpolation->GetTarget();
		}
		operator DataType() const
		{
			return Interpolation->GetCurrent();
		}
		bool operator==(DataType const & InOther) const
		{
			return InOther == Interpolation->GetTarget();
		}
		bool IsInterpolating() const
		{
			return bInterpolating;
		}

		//----- setter -----
		Interpolator<DataType>& operator=(DataType const & InTarget)
		{
			Interpolation->SetTarget(InTarget);
			//std::cout << "starting interpolation from: " << (std::string)Start << " to " << (std::string)Target << ".\n";
			InterpolationStarted = std::chrono::system_clock::now();
			bInterpolating = true;

			return *this;
		}

		//----- interpolation -----
		void Update()
		{
			if (bInterpolating)
			{
				TimeType Now = std::chrono::system_clock::now();
				bInterpolating = Interpolation->Interpolate(std::chrono::duration_cast<std::chrono::duration<float>>(Now - InterpolationStarted));
			}
		}

	private:

		InterpolationFunction<DataType>* Interpolation;
		//DataType Current;
		/*DataType Start;
		DataType Target;*/
		TimeType InterpolationStarted;
		bool bInterpolating;
	};
}
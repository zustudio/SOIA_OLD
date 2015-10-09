
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
		{
			Interpolation->SetCurrent(InData);
		}

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
			bInterpolating = true;

			return *this;
		}

		//----- interpolation -----
		void Update()
		{
			if (bInterpolating)
			{
				bInterpolating = Interpolation->Interpolate();
			}
		}

	private:

		InterpolationFunction<DataType>* Interpolation;
		//DataType Current;
		/*DataType Start;
		DataType Target;*/
		bool bInterpolating;
	};
}
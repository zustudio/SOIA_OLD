
#pragma once

#include "Environment/Reflection/Element/Public/RContainer.h"

namespace Supervisor
{

	template<typename FromT, typename ToT>
	struct TypeConversion
	{
		typedef FromT FromType;
		typedef ToT ToType;
		typedef ToType(*ConversionFuncType)(const FromType&);
		TypeConversion(ConversionFuncType InConversionFunc) :
			ConversionFunc(InConversionFunc)
		{}
		ToType Execute(const FromType& InFromObject)
		{
			return ConversionFunc(InFromObject);
		}
		ConversionFuncType ConversionFunc;
	};


	/* custom type conversion action */
	template<typename FromContainerType, typename ToContainerType, typename ConversionType>
	struct MultipleConversion
	{
		typedef std::vector<typename ConversionType::FromType>(*AccessorFuncType)(const FromContainerType&);
		typedef ToContainerType(*CreatorFuncType)(const std::vector<typename ConversionType::ToType>&);

		MultipleConversion(AccessorFuncType InAccessorFunc, CreatorFuncType InCreatorFunc) :
			AccessorFunc(InAccessorFunc),
			CreatorFunc(InCreatorFunc)
		{}

		ToContainerType Execute(const FromContainerType& InFromContainer, ConversionType InConversion)
		{
			std::vector<ConversionType::FromType> vector = AccessorFunc(InFromContainer);
			std::vector<ConversionType::ToType> result;
			for (auto item : vector)
			{
				result.push_back(InConversion.Execute(item));
			}
			return CreatorFunc(result);
		}

		AccessorFuncType AccessorFunc;
		CreatorFuncType CreatorFunc;

	};





	class DLLIMPEXP ServiceProvider
	{
	public:
		////////////////////////////////////////////////////////////////
		// Functions
		//----- Intializing -----

		/// Constructor.
		ServiceProvider();

		////////////////////////////////////////////////////////////////
		// Variables

		Environment::RContainer Services;


	};
}
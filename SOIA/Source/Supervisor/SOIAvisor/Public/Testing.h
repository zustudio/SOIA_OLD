
#pragma once

#include "ConstExprByteParser.h"
//#include "StringParser.h"
#include <iostream>
#include <string>
#include "LinearFunction.h"
#include "RContainer.h"
using namespace ZABS::Math;

namespace Environment
{

	
	


	class X
	{ 
		
	public:
		template<int X>
		void Go()
		{
			RContainer container = RContainer(Range<int>(0, 1000));
			std::cout << std::string(container.GetClass()->GetType()) << std::endl;

			auto reflection = container.CreateReflection();
			for (auto attribute : reflection.Attributes)
			{
				std::string typeString = attribute.GetTypeID();
				std::cout << typeString << " = " << GetAtomReflectionProvider()->GetReflection(typeString)->ObjectToString(attribute) << std::endl;
			}
		}
	};
}
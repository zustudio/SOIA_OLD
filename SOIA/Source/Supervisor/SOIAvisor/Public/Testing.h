
#pragma once

#include "CharReplacer.h"
//#include "StringParser.h"
#include "RContainer.h"
#include "Range.h"
#include <iostream>
#include <string>
#include "LinearFunction.h"
using namespace ZABS::Math;

namespace Environment
{

	
	


	class X
	{ 
		
			//static constexpr const auto typelit = TypeCharArrayLiteral<Range<int>>::Create();
	public:
		template<int X>
		void Go()
		{
			/*static constexpr const auto charArray = typelit.text_ptr;
			static constexpr const int length = typelit.text_size;
			std::cout << (int)*(charArray - 14) << " vs " << (int)' ' << std::endl;
			static const std::string String = std::string(charArray, charArray + length);
			std::cout << String;*/

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
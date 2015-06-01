
#pragma once

#include "ConstExprByteParser.h"
//#include "StringParser.h"
#include <iostream>
#include <string>
#include "LinearFunction.h"
using namespace ZABS::Math;

namespace Environment
{

	
	


	class X
	{ 
		//static constexpr const auto input = literal_str("class std::vector<class std::vector<class allocator>, std::another allocator>, class Environment::Test");
		using textT = CharArray_FUNCTION_<std::vector<LinearFunction>>;
		static constexpr const auto input = literal_str(textT::Pointer, textT::Size());
		static constexpr const auto pattern = literal_str("class ");
		static constexpr const auto replacement = literal_str("**");
		static constexpr const auto replacer = CharReplacer<void*, nullptr>(pattern, replacement, input);

		static constexpr const auto input2 = literal_str("NOPE");
		static constexpr const auto pattern2 = literal_str("**");
		static constexpr const auto replacement2 = literal_str("X");
		static constexpr const auto replacer2 = CharReplacer<const CharReplacer<void*, nullptr>&, replacer>(pattern2, replacement2, input2);
	public:
		template<int X>
		void Go()
		{
			constexpr const auto c = *(literal_str("ABC").text_ptr + 2); // << std::endl;
			//constexpr const int int_arr[] = ConstValues::i_arr;

			constexpr const auto str = literal_str("DIES ist Ein InTer...");
			constexpr const char* text_ptr = str.text_ptr;
			const auto arr = lookup_table<>::get(text_ptr);


			//constexpr const char cSome = Decode4Bytes(replacer.FindNthItem_Worker(decltype(replacer)::CheckPointDelta, -1, -1, -1), 0);
			

			constexpr const char c0 = replacer2.FindNthItem(0);
			constexpr const char someC = replacer2.FindNthItem(1);
			constexpr const char c2 = replacer2.FindNthItem(2);
			constexpr const char c3 = replacer2.FindNthItem(3);
			constexpr const char c4 = replacer2.FindNthItem(4);
			constexpr const char c5 = replacer2.FindNthItem(5);

			const auto carr = SetReplacer<decltype(replacer2), replacer2>::ReplacerToArray<>::get();

			const int rep2size = replacer2.GetSize_Input();
			constexpr const int rep2newsize = replacer2.Size;
			const int rep1size = replacer.GetSize_Input();
			int a = 1;
			constexpr const int rep1newsize = replacer.Size;
				//replacer.FindZeroCharGuessing(replacer.Size);
			
			constexpr const char someC0 = Decode4Bytes(replacer2.Check1, 0);

			//std::string t = carr.data();

			//CharArray_4 arr4;
			//std::cout << StringStruct<X>::Value << std::endl;
			constexpr const char String[] = "Wie geht es dir?";
			//const auto arr = CreateByteArray<CharArray_Message::Size(), CharArray_Message::Pointer>::lookup_table<>::get();

			//std::cout << std::string(/*arr.data()*/CharArray_4::Pointer.Pointer) << std::endl;
		}
	};
}
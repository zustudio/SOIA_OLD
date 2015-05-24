
#include "Supervisor/Core/Classes/PrivateDefinitions.h"

// include class
#include "Supervisor/Core/Public/ServiceProvider.h"
using namespace Supervisor;
using namespace Environment;

// include SOIA
#include "Supervisor/Console/Public/ConsoleService.h"
#include "Apprentice/SSt/Public/Engine_SSt.h"
using namespace Apprentice;

// TEST
#include "Supervisor/Logica/Public/SchroedingerApplication.h"
#include "Environment/Mathematics/Runtime/Public/Constant.h"
#include "Environment/File/Public/SaveFile.h"
#include "Environment\Meta\Public\StringParser.h"
using namespace Environment::Meta;
#include <iostream>
#include <array>

#include "Environment/Global/Public/GlobalsImport.h"



ServiceProvider::ServiceProvider() 
	: 
	Services(RContainer(Range<int>(0, 1000000)))
{
	////////////////////////////////////////////////////////////////////////////////////

	auto conv = TypeConversion<std::string, int>([](const std::string& InString) {return std::atoi(InString.c_str()); });
	int inew = conv.Execute("1234");

	auto multconv = MultipleConversion<std::vector<std::string>, std::vector<int>, TypeConversion<std::string, int> >(
		[](const std::vector<std::string>& InVector) {return std::vector<std::string>(InVector); },
		[](const std::vector<int>& InVector) {return std::vector<int>(InVector); });

	auto i_vector = multconv.Execute({ "1235", "456" }, conv);


	constexpr const char* name = TypeName<Element_ID>::Get();
	constexpr const char c1 = *name;
	constexpr const char c2 = *(name + 1);
	constexpr const char c3 = *(name + 2);
	static_assert(c3 == 'v', "ERROR: c3 did not const evaluate to v");

	
	constexpr const auto c5 = NthChar<CharArray_FUNCTION_<int>::Pointer>::Do(4);

	static_assert(c5 == 'r', "c5 is not r!");

	//constexpr const auto list = CreateTypeCharListObject<int, 0, 1, 2, 3, 4, 5, 6>();
	//constexpr const auto c6 = list.Get(5);
	//static_assert(c6 == 'o', "c6 is not o");

	//constexpr const auto test = TEST<int>::file::arg;
	//constexpr const auto c4 = NthChar<TEST<int>::file::arg , 1>::value;

	//constexpr CreateList<int, Plus<int, 3>, 1, 2, 3, 4>::value addList;
	//static_assert(addList.Get(1) == 5, "");

	using listType = ConstExprList<int, 1, 2, 3, 4>;

	//using listType2 =  Insert<1, listType, 5, 6>;

	//const auto i1 = CreateArray<ConstExprList<char, 'a', 'b', 'c'>, 3, 3>().values;

	//const std::string s_i1 = std::string(i1);

	//using list = CreateTestList<20>::value;
	/*using list2 = CreateTestList<400>::value;
	constexpr const auto el = list2::Get<list2::Size - 1>();*/
	//static_assert(Array<4>::value[0]== 0, "1 is not 1");

	//static_assert(v2 == 6, "");

	using list = ConstExprList<int, 1, 2, 3, 4, 5, 6, 7, 8, 4, 5, 6, 4, 5, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20>;
	using quest = ConstExprList<int, 4, 5>;
	using replacement = ConstExprList<int, 42>;



	//const auto intArray = ListToArrayObject<list>::Result().Value;
		//UsingEveryIndex<list::Size, Action<CreateArray, ActionArgs<list> > >::Result().values;

	constexpr const int typeStringSize = CharArray_FUNCTION_<int>::Size();
	using typelist = CharArrayToList<CharArray_FUNCTION_<int> >;

	//using typelist = UsingEveryIndex<CharArray_FUNCTION_<int>::Size(), Action<ListFromIndices, ActionArgs<char, NthChar<TypeString<int>::FunctionName> > > >::Result::Value;
	const auto charArray = ListToArrayObject<typelist>().Value;
	//const std::string charString = charArray;

	using charList = CharArrayToList<CharArray_1>;
	using repList = CharArrayToList<CharArray_2>;
	const std::string charString2 = ListToArrayObject<charList>().Value;

	const std::string replacedType = ListToArrayObject<Replace<typelist, charList, repList> >().Value;

	using partList = MatchingSublist<typelist, charList, 0>;
	const auto partArray = ListToArrayObject<partList>().Value;

	//constexpr const auto beginOfRes = UsingEveryIndex<list::Size, Action<PatternMatch, ActionArgs<list, ConstExprList<int, 4, 5, 6> > > >::Result::FindNthWord(1);
	using matchFunc = list::MatchPattern<quest>;
	constexpr const auto beginOfRes = matchFunc::FindNthWord(1);
	//using matchList = UsingEveryIndex<matchFunc::Count() * 2, Action<ListFromIndices, ActionArgs<int, matchFunc::NthWordToList> > >::Result::Value;
	//using matchList = Replace_Helper<list, quest, replacement>::PatternMatches;
	using replacedList = Replace<list, quest, replacement>; //UsingEveryIndex<list::Size + matchList::Size / 2 * (replacement::Size - quest::Size), Action<ReplaceAction, ActionArgs<list, replacement, matchList> > >::Result::Result;
	const auto replacedArray = ListToArrayObject<replacedList>().Value;
	std::vector<int> v_replaced;
	v_replaced.assign(replacedArray, replacedArray + replacedList::Size);


	//static_assert(beginOfRes == 9, "res does not begin at 9!");

	constexpr auto r1 = list::Get(9);

	////////////////////////////////////////////////////////////////////////////////////


	std::regex pattern("class (\\w+) \\*");
	auto result = std::smatch();
	std::string test = "class test *";
	bool success = std::regex_match(test, result, pattern);


	Constant* c = new Constant(123.4);
	Constant* next = new Constant(5);
	c->Next = next;
	Services.Register(c, "constant");
	Services.Register(next, "next");


	std::cout << "writing to file..." << std::endl;

	//write
	SaveFile* of = new SaveFile("TEST.txt", true);
	of->Content.push_back((RElement*)this);
	of->Write();
	delete of;

	std::cout << "reading from file..." << std::endl;

	//read
	SaveFile sf = SaveFile("TEST.txt", false);
	sf.Read();

	std::cout << "interpreting result..." << std::endl;
	RElement** pp_c = sf.Content[0].CastTo<RElement*>();
	std::cout << ((Constant*)*pp_c)->myValue;

	RClass* c_class = c->GetClass();

	Constant* def_c = (Constant*)c_class->GetDefaultObject();

	std::cout << "default val: " << def_c->myValue << std::endl;

	double i = 789.1;
	VoidPointer p = VoidPointer(i);
	ElementReflection r = ElementReflection({ *new Element_ID(), p });
	def_c->LoadReflection(r, false);

	std::cout << "new value" << def_c->myValue << std::endl;


	std::cout << "creating services..." << std::endl;

	auto console = Services.Register(new ConsoleService(Services), "Console");
	auto engine = Services.Register(new Engine_SSt(Services), "Engine");

	Services.GetElement<RApplication>(console)->Start();
	Services.GetElement<RApplication>(engine)->Start();

	while (true)
	{ }
}

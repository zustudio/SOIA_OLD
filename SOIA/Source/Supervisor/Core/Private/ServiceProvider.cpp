
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
#include <iostream>

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



	const int id = StaticType();
	std::cout << id;




	////////////////////////////////////////////////////////////////////////////////////


	std::regex pattern("class (\\w+) \\*");
	auto result = std::smatch();
	bool success = std::regex_match(std::string("class test *"), result, pattern);


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

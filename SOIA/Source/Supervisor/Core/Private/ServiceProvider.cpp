
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
#include "Environment/Mathematics/Runtime/Public/Constant.h"
#include "Environment/File/Public/SaveFile.h"
#include <iostream>

ServiceProvider::ServiceProvider() 
	: 
	Services(RContainer(Range<int>(0, 1000000)))
{


	

	Constant c = Constant(123.4);

	//write
	SaveFile* of = new SaveFile("../../Binaries/TEST.txt", true);
	of->Content.push_back((RElement*)&c);
	of->Write();
	delete of;


	//read
	SaveFile sf = SaveFile("../../Binaries/TEST.txt", false);
	sf.Read();
	RElement** pp_c = sf.Content[0].CastTo<RElement*>();
	std::cout << ((Constant*)*pp_c)->myValue;

	RClass* c_class = c.GetClass();

	Constant* def_c = (Constant*)c_class->GetDefaultObject();

	std::cout << "default val: " << def_c->myValue << std::endl;

	double i = 789.1;
	VoidPointer p = VoidPointer(i);
	ElementReflection r = ElementReflection({ p });
	def_c->LoadReflection(r);

	std::cout << "new value" << def_c->myValue << std::endl;


	auto console = Services.Register(new ConsoleService(Services), "Console");
	auto engine = Services.Register(new Engine_SSt(Services), "Engine");

	Services.GetElement<RApplication>(console)->Start();
	Services.GetElement<RApplication>(engine)->Start();

	while (true)
	{ }
}

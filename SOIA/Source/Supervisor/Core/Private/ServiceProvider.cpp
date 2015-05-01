
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
#include "Environment/File/Public/SaveFile.h"
#include "Environment/File/Public/TextFile.h"
#include <sstream>
#include <iostream>

ServiceProvider::ServiceProvider() 
	: 
	Services(RContainer(Range<int>(0, 1000000)))
{

	TextFile* fileO = new TextFile("../../Binaries/TEST.txt", true);
	fileO->Content.push_back(VoidPointer(*new std::string("<<double>[1234.5]>")));
	fileO->Write();
	delete fileO;

	SaveFile file = SaveFile("../../Binaries/TEST.txt", false);
	file.Read();

	double* iIn = file.Content[0].CastTo<double>();
	std::cout << "result: " << *iIn << std::endl;



	auto console = Services.Register(new ConsoleService(Services), "Console");
	auto engine = Services.Register(new Engine_SSt(Services), "Engine");

	Services.GetElement<RApplication>(console)->Start();
	Services.GetElement<RApplication>(engine)->Start();

	while (true)
	{ }
}

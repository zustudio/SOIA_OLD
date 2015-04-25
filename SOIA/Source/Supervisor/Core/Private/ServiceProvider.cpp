
#include "Supervisor/Core/Classes/PrivateDefinitions.h"

// include class
#include "Supervisor/Core/Public/ServiceProvider.h"
using namespace Supervisor;
using namespace Environment;

// include SOIA
#include "Supervisor/Console/Public/ConsoleService.h"
#include "Apprentice/SSt/Public/Engine_SSt.h"
using namespace Apprentice;


ServiceProvider::ServiceProvider() 
	: 
	Services(RContainer(Range<int>(0, 1000000)))
{
	int x;
	int& rx = x;

	SO::Base::VoidPointer p = SO::Base::VoidPointer(rx);
	int& rx2 = p.GetReference<int>();

	auto console = Services.Register(new ConsoleService(Services), "Console");
	auto engine = Services.Register(new Engine_SSt(Services), "Engine");

	Services.GetElement<RApplication>(console)->Start();
	Services.GetElement<RApplication>(engine)->Start();

	while (true)
	{ }
}

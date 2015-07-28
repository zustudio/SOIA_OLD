
#include "Definitions.h"

#include "StdDialogue.h"
#include "RWrapper.h"
using namespace Environment;

#include "PersistentRuntime.h"
using namespace Supervisor;


int main()
{
	PersistentRuntime::Initialize(RWrapper<StdDialogue>::StaticClass());
	PersistentRuntime::Run();
}

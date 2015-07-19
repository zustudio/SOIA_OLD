
#pragma once

#include "Definitions.h"

#include "Workspace.h"
using namespace Supervisor;

#include "RContainer.h"
#include "ContainerProvider.h"
using namespace Environment;

void Workspace::Initialize()
{
	// create top level container
	RContainer* topContainer = new RContainer(Range<int>(0, 10));
	SetTopContainer(topContainer);

	// create top level tools


}


#include "Definitions.h"

#include "PipelineTool.h"
using namespace Supervisor;
using namespace Environment;

PipelineTool::PipelineTool(const RPointer<RDialogue>& InDialogue)
	: BaseType(InDialogue)
{

}

bool PipelineTool::cmd_add()
{
	return true;
}
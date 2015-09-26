
#include "Definitions.h"

#include "PipelineTool.h"
using namespace Supervisor;
using namespace Environment;

PipelineTool::PipelineTool()
	: BaseType(),
	PipeStart(nullptr, TypeID("int")),
	PipeEnd(nullptr, TypeID("int"))
{
	ReflectAttributes();
}

bool PipelineTool::cmd_listpipes()
{
	for (auto pipe : Pipes)
	{
		Dialogue->WriteLine(pipe->TargetFunction->GetName());
	}
	return true;
}

bool PipelineTool::cmd_pipe(Pipe *& OutPipe, const std::string & InName)
{
	OutPipe = nullptr;

	for (auto pipe : Pipes)
	{
		if (pipe->TargetFunction->GetName() == InName)
		{
			OutPipe = pipe;
			return true;
		}
	}

	return true;
}

bool PipelineTool::cmd_add(Environment::RFunction* const &InFunction)
{
	Pipes.push_back(new Pipe(InFunction));
	(*(Pipes.end() - 1))->Start();
	return true;
}

bool PipelineTool::cmd_link(Pipe* const & OutPipe, int const & OutArgNum, Pipe * const & InPipe, int const & InArgNum)
{
	OutPipe->Output[OutArgNum].Pair(&InPipe->Input[InArgNum]);
	return true;
}

bool PipelineTool::cmd_execute(int const& Number)
{
	PipeStart.Pair(&(*Pipes.begin())->Input[0]);
	PipeStart.Write(VoidPointer(new int(Number)));
	return true;
}

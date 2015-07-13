
#include "Definitions.h"

#include "RGraphTool2D.h"
using namespace Supervisor;

#include <iostream>

RGraphTool::RGraphTool(const RPointer<RDialogue>& InDialogue)
	: BaseType(InDialogue)
{
	ReflectAttributes();
}

bool RGraphTool::cmd_pointlist()
{
	for (auto point : Points)
	{
		Dialogue->WriteLine("( " + std::to_string(point.X) + " | " + std::to_string(point.Y) + " )");
	}
	return true;
}

bool RGraphTool::pipe_addpoint(const double & InX, const double & InY)
{
	Points.push_back(Vector2D<double>(InX, InY));
	return true;
}

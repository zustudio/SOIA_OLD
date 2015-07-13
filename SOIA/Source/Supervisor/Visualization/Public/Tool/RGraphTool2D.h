
#pragma once

#include "RTool.h"

#include "Vector2D.h"

namespace Supervisor
{
	RCLASS(RGraphTool, RTool);
	class LIBIMPEXP RGraphTool : public RGraphTool_Base
	{
		RCLASS_BEGIN();

		RGraphTool(const RPointer<RDialogue>& InDialogue = RPointer<RDialogue>(nullptr));

		RFUNCTION(cmd_pointlist)
			bool cmd_pointlist();

		RFUNCTION(pipe_addpoint)
			bool pipe_addpoint(const double& InX, const double& InY);

		std::vector<Vector2D<double>> Points;

		RCLASS_END();
	};
}
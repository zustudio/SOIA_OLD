
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

		RFUNCTION(cmd_listpoints)
			bool cmd_listpoints();

		RFUNCTION(pipe_AddPoint)
			bool pipe_AddPoint(const double& InX, const double& InY);

		std::vector<Vector2D<double>> Points;

		RCLASS_END();
	};
}
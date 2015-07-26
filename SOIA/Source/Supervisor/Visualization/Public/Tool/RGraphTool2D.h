
#pragma once

#include "TTool.h"

#include "Vector2D.h"

namespace Supervisor
{
	RCLASS(RGraphTool, TTool);
	class LIBIMPEXP RGraphTool : public RGraphTool_Base
	{
		RCLASS_BEGIN()

		RGraphTool();

		RFUNCTION(cmd_pointlist)
			bool cmd_pointlist();

		RFUNCTION(pipe_addpoint)
			bool pipe_addpoint(const double& InX, const double& InY);

		std::vector<Vector2D<double>> Points;

		RCLASS_END()
	};
}
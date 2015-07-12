
#pragma once

#include "Control.h"

#include "Matrix2D.h"

namespace Environment
{
	class LIBIMPEXP CTable : public Control
	{
	public:
		CTable(Window_Base* NewWindow = nullptr, const cPoint &NewLoc = cPoint(), const cPoint &NewSize = cPoint());

		virtual void Draw() override;

		fPoint GetCellLocation(int X, int Y);

		Matrix2D<double> Matrix;
	};
}
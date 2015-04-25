
#pragma once

#include "Control.h"

#include "Environment/Mathematics/DataStructures/Public/Matrix2D.h"

namespace Graphics
{
	class DLLIMPEXP CTable : public Control
	{
	public:
		CTable(SO::Window_Base* NewWindow = nullptr, const cPoint &NewLoc = cPoint(), const cPoint &NewSize = cPoint());

		virtual void Draw() override;

		fPoint GetCellLocation(int X, int Y);

		ZABS::Math::Matrix2D<double> Matrix;
	};
}
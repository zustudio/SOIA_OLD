#pragma once

namespace SO
{
	namespace Drawing
	{
		class fPoint;
		class fColor;

		enum CanvasObjT
		{
			Null,
			Line,
			Rectangle
		};

		class fCanvasObject
		{
		public:
			CanvasObjT Type;
			fPoint* P1;
			fPoint* P2;
			fColor* Color;

			fCanvasObject(CanvasObjT NewType, const fPoint &NewP1, const fPoint &NewP2, const fColor &NewColor);
			~fCanvasObject();
		};
	}
}
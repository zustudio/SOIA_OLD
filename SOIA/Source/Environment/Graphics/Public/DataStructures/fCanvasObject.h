#pragma once

namespace Graphics
{
	class fPoint;
	class fColor;

	enum CanvasObjT
	{
		Null,
		Line,
		Arrow,
		Rectangle,
		FilledRectangle,
		Text,
		Custom
	};

	class fCanvasObject
	{
	public:
		///////////////////////////////////////////////////////////
		// functions
		//---- init ----
		fCanvasObject(CanvasObjT NewType, const fPoint &NewP1, const fPoint &NewP2, const fColor &NewColor, void *NewContent = nullptr);
		virtual ~fCanvasObject();

		//---- custom object pseudo-interface ----
		virtual std::vector<fCanvasObject*>* GetCustomParts();
		virtual void Highlight(bool bEnable);

		//////////////////////////////////////////////////////////
		// properties
		CanvasObjT Type;
		fPoint* P1;
		fPoint* P2;
		fColor* Color;
		void* Content;
	protected:
		std::vector<fCanvasObject*> CustomParts;

	};
}

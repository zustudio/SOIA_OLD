
#pragma once

#include "TMainTool.h"

#include "BlackBoardWindow.h"
#include "TextBoxDialogue.h"

namespace Supervisor
{
	RCLASS(TBlackBoard, TMainTool)
	class LIBIMPEXP TBlackBoard : public TBlackBoard_Base
	{
		RCLASS_BEGIN()

	public:
		///\name ctor
		///\{
			TBlackBoard();
			virtual ~TBlackBoard();
		///\}

		///\name main loop
		///\{
			virtual void Main() override;
		///\}

	private:
		BlackBoardWindow* Window;

		RCLASS_END()
	};
}
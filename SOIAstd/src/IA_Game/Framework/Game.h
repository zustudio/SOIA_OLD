// SOIAme.h

#pragma once

namespace IA {

	class Game
	{
		///////////////////////////////////////////////////////////////////////
		// game
	public:
		virtual Data* CalculateResult(Data* Input);

		///////////////////////////////////////////////////////////////////////
		// io
	public:
		virtual Data* IFuncResultOfAction(Data* Input);

		///////////////////////////////////////////////////////////////////////
		// init
	public:
		virtual void init();
	};
}

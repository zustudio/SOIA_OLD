#pragma once

#include <vector>
#include <string>

#include "Engine.h"

#include "IData.h"
#include "MTypes.h"
#include "MText.h"
#include "MNET_Base.h"

#include "SDL.h"

using namespace IA::Def_MTypes;

SDL_Modules_Init

namespace IA
{

	class Data_SSt : public MText< MTypes< MNET_Base <IData> > >
	{
	public:
		Data_SSt(int NewContent = 0, const std::string &NewText = "", DataType NewDataType = DataType::Content) : MText(NewText, NewDataType, NewContent)
		{
			registerM(MText);
			registerM(MTypes);
			registerM(MNET_Base);
		};
	};

	class Game;
	class Engine_SSt : public Engine
	{
	public:
		///////////////////////////////////////
		// vars
		Data_SSt* Knowledge;
		Data_SSt* Action;
		Data_SSt* Result;
		Data_SSt* Visible;
		Data_SSt* Current;

		///////////////////////////////////////
		// functions
		//----  init   ----
		Engine_SSt(IA::Game* newGame);
		virtual ~Engine_SSt();
		//----  vars   ----
		virtual IData* getDataStart() override;
		//----  tick   ----
		virtual void Tick() override;
	};
}

#pragma once

#include "Engine.h"
#include "IData.h"
	#include "MNET_Base.h"
	#include "MText.h"
	#include "MTypes.h"
	#include "MSimDec.h"
	#include "MDebug.h"

#include "SDL.h"

SDL_Modules_Init

namespace IA
{

	class Data_SSt : public  MSimDec< MDebug <MText< MNET_Base <IData> > > >
	{ 
	public:
		Data_SSt(int NewContent = 0, const std::string &NewText = "", DataType NewDataType = DataType::Content) : MSimDec(NewDataType, NewText, NewContent)
		{
			registerM(MDebug);
			registerM(MText);
			registerM(MSimDec);
			registerM(MTypes);
			registerM(MNET_Base);
		}
		virtual ~Data_SSt() {}
	};

	class Engine_SSt : public Engine
	{
	public:
		///////////////////////////////////////
		// functions
		//----  init   ----
		Engine_SSt(IA::Game* newGame, SO::Com::ComService* Up);
		virtual ~Engine_SSt();
		//----  main   ----
		virtual void Tick() override;
		virtual void ReIntegrate(Data_SSt* X);
		//----  vars   ----
		virtual IData* getDataStart() override;
		virtual SO::Debug::Statistics& getActionStatistics() override;
		virtual SO::Debug::Statistics& getResultStatistics() override;


	private:
		///////////////////////////////////////
		// vars
		//---- data pointer ----
		Data_SSt* Knowledge;
		Data_SSt* Action;
		Data_SSt* Result;
		Data_SSt* Visible;
		Data_SSt* Current;
		//---- stats ----
		SO::Debug::Statistics ActionStats;
		SO::Debug::Statistics ResultStats;

	};
}

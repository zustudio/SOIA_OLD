#pragma once

#include "Engine.h"
#include "IData.h"
	#include "MNET_Base.h"

#include "SDL.h"

#undef NEWDATA
#define NEWDATA(content) new DATA(content)

SDL_Modules_Init

namespace IA
{
	class Data_SSt : public  MNET_Base <IData>
	{
	public:
		Data_SSt(int NewContent = 0) : MNET_Base<IData>(NewContent)
		{
			if (!checkM(MNET_Base))
			{
				registerM(MNET_Base);
			}
		}
		virtual ~Data_SSt() {}

		void DataLog(const std::string &Message)
		{
				std::cout << Message << std::endl;
		}
	};
	
	class Engine_SSt : public Engine
	{
	public:
		///////////////////////////////////////
		// functions
		//----  init   ----
		Engine_SSt(IA::Game* newGame);
		virtual ~Engine_SSt();
		//----  main   ----
		virtual void Tick() override;
		virtual void ReIntegrate(Data_SSt* X);
		//----  vars   ----
		virtual std::string getEngineName() override;
		virtual IData* getDataStart() override;

	private:
		///////////////////////////////////////
		// vars
		//---- data pointer ----
		Data_SSt* Knowledge;
		Data_SSt* Action;
		Data_SSt* Result;
		Data_SSt* Visible;
		Data_SSt* Current;

	};
}

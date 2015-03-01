
#pragma once

#include "IIDebuggable.h"

////////////////////////////////////////////////////////////////////////
// Definitions
/*Macro for faster logging. Preferebly logs via MDebug module and IIDebuggable interface, else via std::cout.*/
#define DataLog(Message)	do { \
								if (checkM(MDebug)) \
									static_cast<DATA*>(this)->ii_Log(SO::Debug::EDebugLevel::Info_SubFunction, Message); \
								else \
									std::cout << Message << std::endl; \
							} while(0)

////////////////////////////////////////////////////////////////////////
// Main class

namespace IA
{
	using namespace SO::Base;

	template <class Super>
	class MDebug : public Super, virtual public SO::Debug::IIDebuggable
	{
	public:
		////////////////////////////////////////////////////////////
		// init
		template<typename... Args>
		MDebug(SO::Com::ComService* NewUp, Args&&... args) : Super(args...)
		{
			IIDebuggable::init(NewUp);
		}
		virtual ~MDebug() {}

		////////////////////////////////////////////////////////////
		// functionality
		virtual void set(int i) override
		{
			//break first, then exec real command
			ii_Break();
			Super::set(i);
		}
		virtual void connect(IData* NewSub) override
		{
			//try to break myself
			ii_Break();

			//try to break my target
			MDebug<Super>* target = dynamic_cast<MDebug<Super>*>(NewSub);
			if (target)
			{
				target->ii_Break();
			}

			//execute real command
			Super::connect(NewSub);
		}

		//////////////////////////////////////////////////
		// IIComOut<-IDebuggable interface
		virtual Handle<ICom>& cGetHandle() override
		{
			auto p_hndl = new Handle<ICom>(this, "MDebug");
			return *p_hndl;
		}
	};
	
}

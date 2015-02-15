
#pragma once

#include "IIDebuggable.h"

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
		MDebug(Args&&... args) : Super(args...), IIDebuggable() {}

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
			return Handle<ICom>();
		}

	};
	
}
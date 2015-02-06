
#pragma once

#include "IDebugObj.h"

namespace IA
{
	using namespace SO::Base;

	template <class Super>
	class MDebug : public Super, public IDebugObj
	{
	public:
		////////////////////////////////////////////////////////////
		// init
		template<typename... Args>
		MDebug(Args&&... args) : Super(args...) {}

		////////////////////////////////////////////////////////////
		// functionality
		virtual void set(int i) override
		{
			ii_break();
			Super::set(i);
		}

	};
	
}
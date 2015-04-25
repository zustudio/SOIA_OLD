
#pragma once

#include "Element_ID.h"

namespace Environment
{
	class DLLIMPEXP RElement
	{
	public:
		RElement() {};
		virtual ~RElement() {};
		void SetID(Element_ID InID);
		Element_ID& GetID();
	private:
		Element_ID ID;
	};
}

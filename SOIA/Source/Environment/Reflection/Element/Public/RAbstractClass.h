
#pragma once

#include "RClass.h"

namespace Environment
{
	class DLLIMPEXP RAbstractClass : public RClass
	{
	public:
		RAbstractClass(const TypeID& InTypeID, const TypeID& InSuperTypeID);
		virtual RElement* GetDefaultObject() override;
		virtual bool IsAbstract() override;
	};
}
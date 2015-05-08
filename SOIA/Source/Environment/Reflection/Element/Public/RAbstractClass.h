
#pragma once

#include "RClass.h"

namespace Environment
{
	class DLLIMPEXP RAbstractClass : public RClass
	{
	public:
		RAbstractClass(const std::string& InTypeID, const std::string& InSuperTypeID);
		virtual RElement* GetDefaultObject() override;
		virtual bool IsAbstract() override;
	};
}
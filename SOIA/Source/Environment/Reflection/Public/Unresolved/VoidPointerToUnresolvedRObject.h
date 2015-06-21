
#pragma once

#include "VoidPointer.h"
#include "ResolveInfoInterface.h"

namespace Environment
{
	class RContainer;
	class LIBIMPEXP VoidPointerToUnresolvedRObject : public VoidPointer
	{
	public:
		typedef void(*ToVoidPointerFunction)(VoidPointerToUnresolvedRObject* InThis);

		/*VoidPointerToUnresolvedRObject(const VoidPointer &ObjToCopy, bool NOP = false)
			: VoidPointer(ObjToCopy)
		{}*/


		template<typename T>
		VoidPointerToUnresolvedRObject(const T &NewObject, ToVoidPointerFunction InResolveFunction, ResolveInfoInterface* InResolveInfo)
			: VoidPointer(NewObject),
			ResolveFunction(InResolveFunction),
			ResolveInfo(InResolveInfo)
		{}

		void Resolve(RContainer* InContainer);
		ResolveInfoInterface* GetResolveInfo();

	private:
		ToVoidPointerFunction ResolveFunction;
		ResolveInfoInterface* ResolveInfo;
	};
}

#pragma once

#include "File_DEPRECATED.h"

namespace Environment
{
	class LIBIMPEXP TextFile : public File_DEPRECATED
	{
	public:
		TextFile(const std::string &InName, bool bWriteFile);
		virtual void PreWrite() override;
		virtual void PostRead() override;
		virtual void WriteObject(const VoidPointer& InObject) override;
		virtual VoidPointer* ReadObject() override;
	};
}
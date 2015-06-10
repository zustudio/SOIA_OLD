
#pragma once

#include "File.h"

namespace Environment
{
	class LIBIMPEXP TextFile : public File
	{
	public:
		TextFile(const std::string &InName, bool bWriteFile);
		virtual void PreWrite() override;
		virtual void PostRead() override;
		virtual void WriteObject(const VoidPointer& InObject) override;
		virtual VoidPointer* ReadObject() override;
	};
}
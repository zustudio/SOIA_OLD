
#pragma once

#include "File.h"

namespace Environment
{
	class DLLIMPEXP TextFile : public File
	{
	public:
		TextFile(const std::string &InName, bool bWriteFile);
		virtual void WriteObject(const VoidPointer& InObject) override;
		virtual VoidPointer* ReadObject() override;
	};
}
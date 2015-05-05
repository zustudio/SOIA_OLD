
#pragma once

#include "File.h"

#include "PropertyTagFactory.h"
#include "FileObjectFactory.h"
#include "Environment/Reflection/Atomic/Public/AtomReflectionProvider.h"

namespace Environment
{
	class DLLIMPEXP SaveFile : public File
	{
	public:
		SaveFile(const std::string &InName, bool bWriteFile);
		virtual void WriteObject(const VoidPointer& InObject) override;
		virtual VoidPointer* ReadObject() override;

	private:
		AtomReflectionProvider ReflectionProvider;
		PropertyTagFactory TagFactory;
		FileObjectFactory ObjectFactory;
	};
}
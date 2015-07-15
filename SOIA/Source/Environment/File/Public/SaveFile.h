
#pragma once

#include "File_DEPRECATED.h"

#include "PropertyTagFactory.h"
#include "FileObjectFactory.h"
#include "AtomReflectionProvider.h"
#include "RContainer.h"

namespace Environment
{
	class LIBIMPEXP SaveFile : public File_DEPRECATED
	{
	public:
		SaveFile(const std::string &InName, bool bWriteFile);

		virtual void PreWrite() override;
		virtual void PostRead() override;

		virtual void WriteObject(const VoidPointer& InObject) override;
		virtual VoidPointer* ReadObject() override;

		RContainer LoadedRElements;
		std::vector<FileObject> FileObjects;
	private:
		PropertyTagFactory TagFactory;
		FileObjectFactory ObjectFactory;
	};
}
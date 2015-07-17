
#pragma once

#include "IOFile.h"

#include "PropertyTagFactory.h"
#include "FileObjectFactory.h"
#include "AtomReflectionProvider.h"
#include "RContainer.h"

namespace Environment
{
	enum class ESaveMode : int
	{
		Single,
		Recursive
	};
	class LIBIMPEXP SaveFile : public IOFile
	{
	public:
		SaveFile(const Path &InName);

		void AddElement(RElement* const & InElement, ESaveMode InSaveMode);

		void Write();
		void Read();
		void PreWrite(std::vector<VoidPointer>& InContainer);
		void PostRead();

		void WriteObject(const VoidPointer& InObject);
		VoidPointer* ReadObject();

		RContainer LoadedRElements;
		std::vector<FileObject> FileObjects;
	private:
		std::vector<VoidPointer> Content;
		PropertyTagFactory TagFactory;
		FileObjectFactory ObjectFactory;
	};
}
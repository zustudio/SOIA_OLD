
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
		RElement* GetElement(int InNum, const std::vector<RElement*>& InReferenced);

		void Write();
		void Read();

	protected:
		void PreWrite(std::vector<VoidPointer>& InContainer);
		void PostRead(FileObject& InFileObject, const std::vector<RElement*>& InReferenced);

		void WriteObject(const VoidPointer& InObject);
		VoidPointer* ReadObject();

		std::vector<FileObject> FileObjects;
	private:
		std::vector<VoidPointer> Content;
		PropertyTagFactory TagFactory;
		FileObjectFactory ObjectFactory;
	};
}
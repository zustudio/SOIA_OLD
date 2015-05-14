
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/File/Public/File.h"

using namespace Environment;

/////////////////////////////////////////////////////////////////
// init
File::File(const std::string &InName, bool bWriteFile)
{
	Name = InName;
	bWriting = bWriteFile;
	if (bWriteFile)
	{
		OutStream = new std::ofstream();
		OutStream->open(Name);
		if (OutStream->is_open())
		{
			std::cout << "Opened file " << Name << std::endl;
		}
	}
	else
	{
		InStream = new std::ifstream();
		InStream->open(Name);
		if (InStream->is_open())
		{
			std::cout << "Opened file " << Name << std::endl;
		}
	}
}

File::~File()
{
	OutStream->close();
}

//////////////////////////////////////////////////
// write to file
void File::Write()
{
	PreWrite();
	for (VoidPointer p_Obj : Content)
	{
		WriteObject(p_Obj);
	}
}

void File::Read()
{
	VoidPointer* readObject;
	do
	{
		readObject = ReadObject();
		if (readObject)
		{
			VoidPointer p = *readObject;
			Content.push_back(p);
		}

	} while (readObject);

	PostRead();
}

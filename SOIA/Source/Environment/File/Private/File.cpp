
#include "Environment/PreProcessor/Classes/PrivateDefinitions.h"

#include "Environment/File/Public/File.h"

using namespace Environment;

/////////////////////////////////////////////////////////////////
// init
File::File(const std::string &InName, bool bWriteFile)
{
	OutStream = nullptr;
	InStream = nullptr;
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
	if (OutStream) OutStream->close();
	if (InStream) InStream->close();
}

//////////////////////////////////////////////////
// write to file
void File::Write()
{
	std::cout << "Preparing writing to file..." << std::endl;
	PreWrite();
	std::cout << "Writing to file..." << std::endl;
	for (VoidPointer p_Obj : Content)
	{
		WriteObject(p_Obj);
	}
}

void File::Read()
{
	std::cout << "Reading from file..." << std::endl;
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
	std::cout << "Processing file..." << std::endl;
	PostRead();
}

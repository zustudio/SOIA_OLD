
#include "Definitions.h"

#include "File.h"
using namespace Environment;

#include "LogProvider.h"

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
			LOGSTATUS("Opened file " + Name);
			//std::cout << "Opened file " << Name << std::endl;
		}
	}
	else
	{
		InStream = new std::ifstream();
		InStream->open(Name);
		if (InStream->is_open())
		{
			LOGSTATUS("Opened file " + Name);
			//std::cout << "Opened file " << Name << std::endl;
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
	LOGSTATUS("Preparing writing to file...");
	PreWrite();
	LOGSTATUS("Writing to file...");
	for (VoidPointer p_Obj : Content)
	{
		WriteObject(p_Obj);
	}
}

void File::Read()
{
	LOGSTATUS("Reading from file...");
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
	LOGSTATUS("Processing file...");
	PostRead();
}

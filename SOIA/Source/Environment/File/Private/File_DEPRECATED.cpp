
#include "Definitions.h"

#include "File_DEPRECATED.h"
using namespace Environment;

#include "LogProvider.h"

/////////////////////////////////////////////////////////////////
// init
File_DEPRECATED::File_DEPRECATED(const std::string &InName, bool bWriteFile)
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

File_DEPRECATED::~File_DEPRECATED()
{
	if (OutStream) OutStream->close();
	if (InStream) InStream->close();
}

//////////////////////////////////////////////////
// write to file
void File_DEPRECATED::Write()
{
	LOGSTATUS("Preparing writing to file...");
	PreWrite();
	LOGSTATUS("Writing to file...");
	for (VoidPointer p_Obj : Content)
	{
		WriteObject(p_Obj);
	}
}

void File_DEPRECATED::Read()
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

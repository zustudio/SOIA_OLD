
#include "Definitions.h"

#include "IOFile.h"
using namespace Environment;

#include "LogProvider.h"

IOFile::IOFile(Path const & InPath)
	: File(InPath),
	InStream(nullptr),
	OutStream(nullptr)
{}

bool IOFile::Open(EFileMode InMode)
{
	bool success = false;
	switch (InMode)
	{
	case Environment::EFileMode::Closed:
	break;
	case Environment::EFileMode::Read:
	{
		InStream = new std::ifstream();
		InStream->open(PathToFile.ToString());
		if (InStream->is_open())
		{
			LOGSTATUS("Opened file " + PathToFile.ToString());
			success = true;
		}
	}
	break;
	case Environment::EFileMode::Write:
	{
		OutStream = new std::ofstream();
		OutStream->open(PathToFile.ToString());
		if (OutStream->is_open())
		{
			LOGSTATUS("Opened file " + PathToFile.ToString());
			success = true;
		}
	}
	break;
	default:
	break;
	}
	return success;
}

bool IOFile::Close()
{
	bool success = false;

	if (InStream)
	{
		InStream->close();
		delete InStream;
		success |= true;
	}
	if (OutStream)
	{
		OutStream->close();
		delete OutStream;
		success |= true;
	}

	return success;
}

std::ofstream& IOFile::GetOutStream()
{
	return *OutStream;
}

std::ifstream& IOFile::GetInStream()
{
	return *InStream;
}


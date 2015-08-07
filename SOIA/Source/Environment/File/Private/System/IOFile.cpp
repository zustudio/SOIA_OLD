
#include "Definitions.h"

#include "IOFile.h"
using namespace Environment;

#include "LogProvider.h"

IOFile::IOFile(Path const & InPath)
	: File(InPath),
	InStream(nullptr),
	OutStream(nullptr),
	CurrentMode(EFileMode::Closed)
{}

bool IOFile::Open(EFileMode InMode)
{
	bool success = false;
	std::fstream* stream = nullptr;
	std::ios::fmtflags flags = 0;

	switch (InMode)
	{
		case EFileMode::Overwrite:
			OutStream = new std::ofstream();
			stream = (std::fstream*)OutStream;
			flags = std::ios::trunc;
			break;
		case EFileMode::Append:
			OutStream = new std::ofstream();
			stream = (std::fstream*)OutStream;
			flags = std::ios::app;
			break;
		case EFileMode::Read:
			InStream = new std::ifstream();
			stream = (std::fstream*)InStream;
			flags = 0;
			break;
		case EFileMode::Closed:
			break;
		default:
			break;
	}

	if (stream)
	{
		stream->open(PathToFile.ToString(), flags);
		if (OutStream->is_open())
		{
			LOGSTATUS("Opened file '" + PathToFile.ToString() + "'.");
			success = true;
		}
		else
		{
			LOG("Could not open file '" + PathToFile.ToString() + "'.", Logger::Severity::Error);
		}
	}
	return success;
}

bool IOFile::Delete()
{
	return std::remove(PathToFile.ToString().c_str()) != 0;
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


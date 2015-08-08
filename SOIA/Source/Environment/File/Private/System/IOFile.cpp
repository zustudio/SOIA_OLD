
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
	std::ios::fmtflags flags = 0;

	switch (InMode)
	{
		case EFileMode::Overwrite:
			flags = std::ios::trunc | std::ios::out;
			OutStream = new std::ofstream(PathToFile.ToString(), flags);
			success = OutStream->is_open();
			break;
		case EFileMode::Append:
			flags = std::ios::app | std::ios::out;
			OutStream = new std::ofstream(PathToFile.ToString(), flags);
			success = OutStream->is_open();
			break;
		case EFileMode::Read:
			flags = std::ios::in;
			InStream = new std::ifstream(PathToFile.ToString(), flags);
			success = InStream->is_open();
			break;
		case EFileMode::Closed:
			break;
		default:
			break;
	}

	if (success == true)
	{
		LOGSTATUS("Opened file '" + PathToFile.ToString() + "'.");
	}
	else
	{
		LOG("Could not open file '" + PathToFile.ToString() + "'.", Logger::Severity::Error);
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


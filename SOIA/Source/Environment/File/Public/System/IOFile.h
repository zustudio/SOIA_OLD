
#pragma once

#include "File.h"

#include <fstream>

namespace Environment
{
	enum class EFileMode : int
	{
		Closed,
		Read,
		Write
	};
	class IOFile : public File
	{
	public:
		IOFile(Path const& InPath);

	protected:
		bool Open(EFileMode InMode);
		bool Close();
		std::ofstream& GetOutStream();
		std::ifstream& GetInStream();

	private:
		EFileMode CurrentMode;
		std::ofstream* OutStream;
		std::ifstream* InStream;
	};
}

#pragma once

#include "File.h"

#include <fstream>

namespace Environment
{
	enum class EFileMode : int
	{
		Closed,
		Read,
		Append,
		Overwrite
	};
	class LIBIMPEXP IOFile : public File
	{
	public:
		////////////////////////////////////////////////////////////////
		// Functions

		//----- init -----
		IOFile(Path const& InPath);

		//----- public accessors ------
		bool Open(EFileMode InMode);
		bool Delete();
		bool Close();

	protected:
		//----- utility for child classes -----

		/// Private getter for outstream.
		std::ofstream& GetOutStream();

		/// Private getter for instream.
		std::ifstream& GetInStream();

		/// Checks for correct file mode
		bool IsCurrentMode(EFileMode InMode);

	private:
		////////////////////////////////////////////////////////////////
		// Variables
		std::ofstream* OutStream;
		std::ifstream* InStream;
		EFileMode CurrentMode;
	};
}
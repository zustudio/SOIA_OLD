
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "CPPExtensions.h"

#include "VoidPointer.h"

namespace SO
{
	exEnum(FileOptions,
		enumElement(TypeTags, 1 << 0);
	);


	class File
	{
	public:
		//////////////////////////////////////////////////////////
		// Functions
		//---- init ----
		File(const std::string &InName, const FileOptions &InOptions);
		//---- deinit -----
		~File();

		//---- write to a file ----
		void Write();
		bool WriteObject(const SO::Base::VoidPointer &InObject);

		/////////////////////////////////////////////////////////
		// Variables
		//---- streams ----
		std::ofstream* OutStream;
		//---- name ----
		std::string Name;
		//---- content ----
		std::vector<SO::Base::VoidPointer> Content;
		//---- options ----
		FileOptions Options;
	};
}


#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "VoidPointer.h"

/* custom extendable enum class (REMOVE)*/
#define exEnum(enumname, operations) class enumname {private: int i; public: enumname(int newI = 0) { i = newI; } operator int() { return i; } operations }
#define enumElement(name, var) static const int name = var

namespace SO
{
	exEnum(FileOptions,
		enumElement(TypeTags, 1 << 0);
	);


	class __declspec(dllexport) File
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

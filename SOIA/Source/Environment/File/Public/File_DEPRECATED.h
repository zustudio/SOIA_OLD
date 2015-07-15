
#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "VoidPointer.h"

namespace Environment
{
	class LIBIMPEXP File_DEPRECATED
	{
	public:
		//////////////////////////////////////////////////////////
		// Functions
		//---- init ----
		File_DEPRECATED(const std::string &InName, bool bWriteFile);
		//---- deinit -----
		~File_DEPRECATED();

		//---- write to a file ----
		void Write();
		void Read();
		virtual void WriteObject(const VoidPointer &InObject) = 0;
		virtual VoidPointer* ReadObject() = 0;

	protected:
		virtual void PreWrite() = 0;
		virtual void PostRead() = 0;

	public:
		/////////////////////////////////////////////////////////
		// Variables
		//---- streams ----
		std::ofstream* OutStream;
		std::ifstream* InStream;
		//---- name ----
		std::string Name;
		//---- content ----
		std::vector<VoidPointer> Content;
		//---- options ----
		bool bWriting;
	};
}

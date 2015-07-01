// c Maxim Urschumzew 2014

#include "stdafx.h"
#include "ConsoleService.h"

#include "SDL_GlobalVars.h"


////////////////////////////////////
// TESTING
#include "File.h"
// ENDTESTING
///////////////////////////////////

using namespace SO;


int main()
{
	std::cout << "#############################c###############\n";
	std::cout << "################## SOIAstd #################\n";
	std::cout << "# Artificial Intelligence Operating System #\n";
	std::cout << "############################################\n";

	////////////////////////////////////
	// TESTING
//	File f = File("TEST.txt", FileOptions::TypeTags);
//	std::string content1 = "This should be my text!!\nAnd this as well ;)\n";
//	int content2 = 1475963;
//	std::string content3 = " <- this is a great number?\n";
//
//	f.Content.push_back(SO::Base::VoidPointer(content1));
//	f.Content.push_back(SO::Base::VoidPointer(content2));
//	f.Content.push_back(SO::Base::VoidPointer(content3));
//	f.Write();
	// ENDTESTING
	///////////////////////////////////

	SOIA::ConsoleService* console = new SOIA::ConsoleService();
	console->Start();

	//t1.join();
	std::cout << "[SOIA]: engine exited";

	return 0;
}

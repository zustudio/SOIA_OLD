
#include "Definitions.h"

#include "BackupTool.h"
using namespace Supervisor;
using namespace Environment;

#include "SaveFile.h"

BackupTool::BackupTool(DialogueInterface* InDialogue)
	: BaseType(InDialogue)
{
	ReflectAttributes();
}

bool BackupTool::cmd_save(const std::string& InElementName, const std::string& InFileName)
{
	bool result = false;
	RElement* element = Container->GetElement<RElement>(InElementName);
	if (element)
	{
		auto file = new SaveFile(InFileName, true);
		file->Content.push_back(element);
		file->Write();
		delete file;
		Dialogue->WriteLine("Saved to file.");
		result = true;
	}
	else
	{
		Dialogue->WriteLine("Could not find element.");
	}
	return result;
}
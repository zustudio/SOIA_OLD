
#include "Definitions.h"

#include "BackupTool.h"
using namespace Supervisor;
using namespace Environment;

#include "SaveFile.h"

BackupTool::BackupTool(const RPointer<RDialogue>& InDialogue)
	: BaseType(InDialogue)
{
	ReflectAttributes();
}

bool BackupTool::cmd_save(RElement* const & InElement, const std::string& InFileName)
{
	bool result = false;
	RElement* element = InElement;
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

bool BackupTool::cmd_load(RElement* const & InElement, const std::string& InFileName)
{
	bool result = false;
	RElement* element = InElement;
	if (element)
	{
		RContainer* Parent = InElement->GetContainer();
		Parent->Unregister(InElement);
		auto file = new SaveFile(InFileName, false);
		file->Read();
		delete InElement;
		const_cast<RElement*&>(InElement) = *file->Content[0].ConvertTo<RElement*>();
		Parent->Register(InElement, InElement->GetID().Name);
		Dialogue->WriteLine("Saved to file.");
		result = true;
		delete file;
	}
	else
	{
		Dialogue->WriteLine("Could not find element.");
	}
	return result;
}
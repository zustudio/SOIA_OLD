
#include "Definitions.h"

#include "BackupTool.h"
using namespace Supervisor;
using namespace Environment;

#include "SaveFile.h"
#include "Thread.h"

BackupTool::BackupTool(const RPointer<RDialogue>& InDialogue)
	: BaseType(InDialogue)
{
	ReflectAttributes();
}

bool BackupTool::cmd_save(RElement* const & InElement, const std::string& InFileName)
{
	bool result = false;
	//RElement* element = InElement;
	//if (element)
	//{
	//	auto file = new SaveFile(InFileName, true);
	//	file->Content.push_back(VoidPointer(element));
	//	file->Write();
	//	delete file;
	//	Dialogue->WriteLine("Saved to file.");
	//	result = true;
	//}
	//else
	//{
	//	Dialogue->WriteLine("Could not find element.");
	//}
	return result;
}

bool BackupTool::cmd_load(RElement* const & InElement, const std::string& InFileName)
{
	bool result = false;
	//RElement* element = InElement;
	//if (element)
	//{
	//	RContainer* Parent = InElement->GetContainer();
	//	auto file = new SaveFile(InFileName, false);
	//	file->Read();
	//	const_cast<RElement*&>(InElement) = *file->Content[0].ConvertTo<RElement*>();
	//	Parent->ReRegister(InElement->GetID(), InElement);
	//	auto newthread = dynamic_cast<Environment::Thread*>(InElement);
	//	if (newthread) newthread->Start();
	//	auto oldthread = dynamic_cast<Environment::Thread*>(element);
	//	if (oldthread) oldthread->Stop();
	//	//delete element;
	//	Dialogue->WriteLine("Saved to file.");
	//	result = true;
	//	delete file;
	//}
	//else
	//{
	//	Dialogue->WriteLine("Could not find element.");
	//}
	return result;
}
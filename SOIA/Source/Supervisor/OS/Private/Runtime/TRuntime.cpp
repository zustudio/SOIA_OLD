
#include "Definitions.h"

#include "TRuntime.h"
using namespace Environment;
using namespace Supervisor;

#include "RGraphTool2D.h"
#include "PipelineTool.h"
#include "RConversionPipes.h"
#include "RGUI.h"
#include "StringMatch.h"
#include "FileSystemProvider.h"
#include "SaveFile.h"
#include "LogProvider.h"
#include "TConsole.h"

TRuntime::TRuntime()
	: BaseType(),
	CurrentDirectory(GetFileSystem()->GetExecutableDirectory())
{
	GetElementReflectionProvider()->RegisterList<
		RGraphTool,
		PipelineTool,
		RConversionPipes>();
	ReflectAttributes();
}

bool TRuntime::cmd_run(TRuntime * const & InRuntime)
{
	for (auto threadElement : ActiveThreads)
	{
		Thread* thread = dynamic_cast<Thread*>(threadElement);
		if (thread)
		{
			thread->Stop();
		}
	}
	Dialogue->WriteLine("Press Enter to change console.");
	InRuntime->Run();
	return true;
}

void TRuntime::Run()
{
	LOGSTATUS("Searching for configured threads...");
	int threadCount = 0;
	for (RElement* activeThreadElement : ActiveThreads)
	{
		Thread* activeThread = dynamic_cast<Thread*>(activeThreadElement);
		if (activeThread)
		{
			activeThread->Start();
			threadCount++;
		}
	}
	if (threadCount)
	{
		LOGSTATUS("Started " + std::to_string(threadCount) + " thread(s).");
	}
	else
	{
		LOGSTATUS("No threads were found. Searching for TConsole child classes in container '" + Container->GetID().Name + "'.");
		auto consoles = Container->GetAllElements<TConsole>();
		if (consoles.size())
		{
			auto console = consoles[0];
			LOGSTATUS("Activating '" + console->GetID().Name + "'.");
			ActiveThreads.push_back(console);
			console->Start();
			threadCount++;
		}
		else
		{
			LOG("No threads could be found, returning", Logger::Severity::Error);
			return;
		}
	}

	for (RElement* activeThreadElement : ActiveThreads)
	{
		Thread* activeThread = dynamic_cast<Thread*>(activeThreadElement);
		if (activeThread)
		{
			activeThread->Join();
		}
	}
}

bool TRuntime::cmd_typelist()
{
	std::vector<TypeID> reflectedAtoms = GetAtomReflectionProvider()->GetTypeList();
	std::vector<TypeID> reflectedElements = GetElementReflectionProvider()->GetTypeList();

	for (auto type : reflectedAtoms)
	{
		Dialogue->WriteLine("Atom\t" + type.ToString());
	}

	for (auto type : reflectedElements)
	{
		Dialogue->WriteLine("Element\t" + type.ToString());
	}
	return true;
}

bool TRuntime::cmd_type(TypeID & OutType, const std::string & InTypeName)
{
	std::vector<TypeID> types = GetElementReflectionProvider()->GetTypeList();
	
	std::vector<std::string> typeStrings;
	for (auto type : types)
	{
		typeStrings.push_back(type.ToString());
	}

	std::string match = StringMatch::GetBest(InTypeName, typeStrings);

	OutType = TypeID(match);

	Dialogue->WriteLine("Matched type: " + match);

	return true;
}

bool TRuntime::cmd_create(const TypeID & InType, const std::string& InName, RContainer* const& InContainer)
{
	bool result = false;
	RClass* objectClass = GetElementReflectionProvider()->GetClass(InType);
	RContainer* targetContainer = InContainer;
	if (objectClass)
	{
		RElement* object = objectClass->GetDefaultObject();

		TTool* tool = dynamic_cast<TTool*>(object);
		if (tool)
		{
			tool->Dialogue = this->Dialogue;
		}

		std::string name = InName;

		if (name == "")
			name = InType.ToEasyString();
		if (targetContainer == nullptr)
			targetContainer = GetContainer();

		targetContainer->Register(object, name);
		result = true;
	}
	return result;
}

bool TRuntime::cmd_rename(RElement* const& InElement, std::string const& InNewName)
{
	bool success = false;

	if (InElement)
	{
		InElement->GetID().Name = InNewName;
	}

	return success;
}

bool TRuntime::cmd_gui(TTool * const & InTool)
{
	static_cast<RGUI*>(InTool->GuiClass->GetDefaultObject())->Start();
	return true;
}

bool TRuntime::cmd_dirlist()
{
	auto dirs = CurrentDirectory.GetSubDirectories(EDirectoryVisibility::All);
	for (auto dir : dirs)
	{
		Dialogue->WriteLine(dir.GetPath().GetName());
	}
	return true;
}

bool TRuntime::cmd_dir(Directory & OutDir, std::string const & InName)
{
	OutDir = Directory(Path(CurrentDirectory.GetPath().ToString() + InName + "/"));
	return true;
}

bool TRuntime::cmd_changedir(const Directory & InDir)
{
	CurrentDirectory = InDir;
	return true;
}

bool TRuntime::cmd_saveproject(Directory const& InDir)
{
	// get directory
	Directory dir = InDir;
	if (InDir.GetPath().ToString() == "")
	{
		dir = Directory(GetFileSystem()->GetExecutableDirectory().GetPath().AppendFolder("Pool").AppendFolder("Projects"));
	}

	// get project
	Element_ID projectID;
	projectID.UniqueIdentifier = 0;
	RContainer* project = GlobalContainer()->GetElement<RContainer>(projectID);

	// save
	return SaveRecursive(dir, project);
}

bool TRuntime::SaveRecursive(Directory const & InDir, RElement* const& InElement)
{
	bool success = true;

	RContainer* InContainer = dynamic_cast<RContainer*>(InElement);
	if (InContainer)
	{
		Directory ContainerDir(Path(""));
		success &= SaveContainer(InDir, InContainer, ContainerDir);
		std::vector<RElement*>& children = InContainer->GetAllElements<RElement>();
		for (RElement*& child : children)
		{
			success &= SaveRecursive(ContainerDir, child);
		}
	}
	else
	{
		success = SaveElement(InDir, InElement);
	}
	return success;
}

bool TRuntime::SaveContainer(Directory const & InDir, RContainer * const & InContainer, Directory & OutContainerDir)
{
	std::string folderName = InContainer->GetID().Name;
	std::string fileName = folderName + ".cont";
	
	OutContainerDir = Directory(InDir.GetPath().AppendFolder(folderName));
	OutContainerDir.Create();

	SaveFile file = SaveFile(OutContainerDir.GetPath().AppendFile(fileName));
	file.AddElement(InContainer, ESaveMode::Single);
	file.Write();
	return true;
}

bool TRuntime::SaveElement(Directory const & InDir, RElement * const & InElement)
{
	std::string fileName = InElement->GetID().Name + ".elem";
	SaveFile file = SaveFile(InDir.GetPath().AppendFile(fileName));
	file.AddElement(InElement, ESaveMode::Recursive);
	file.Write();
	return true;
}

bool TRuntime::cmd_loadproject(Directory const & InDir)
{
	std::vector<RElement*> AllElements;
	LoadRecursive(InDir, AllElements);
	return false;
}

bool TRuntime::LoadRecursive(Directory const & InDir, std::vector<RElement*>& OutAllElements)
{
	std::vector<Directory> subDirectories = InDir.GetSubDirectories();
	std::vector<SaveFile> files = InDir.GetFiles<SaveFile>();

	for (Directory subDirectory : subDirectories)
	{
		RContainer* container = nullptr;
		std::vector<RElement*> subElements;
		std::string containerElemFileName = subDirectory.GetPath().GetBaseName();
		auto iter_containerElemFile = Find(files, containerElemFileName, 
		[](const SaveFile& InSaveFile) -> std::string
		{
			return InSaveFile.GetPath().GetBaseName();
		});
		
		if (iter_containerElemFile != files.end())
		{
			LoadRecursive(subDirectory, subElements);
			LoadContainer(const_cast<SaveFile&>(*iter_containerElemFile), subElements, container);
			files.erase(iter_containerElemFile);
			OutAllElements.push_back(container);
		}
	}

	for (SaveFile file : files)
	{
		RElement* OutElement = nullptr;
		LoadElement(file, OutElement);
		OutAllElements.push_back(OutElement);
	}

	return true;
}

bool TRuntime::LoadContainer(SaveFile& InSaveFile, std::vector<RElement*> const & InChildren, RContainer *& OutContainer)
{
	InSaveFile.Read();
	OutContainer = dynamic_cast<RContainer*>(InSaveFile.GetElement(0, InChildren));
	return bool(OutContainer);
}

bool TRuntime::LoadElement(SaveFile& InSaveFile, RElement *& OutElement)
{
	InSaveFile.Read();
	OutElement = InSaveFile.GetElement(0, {});
	return true;
}







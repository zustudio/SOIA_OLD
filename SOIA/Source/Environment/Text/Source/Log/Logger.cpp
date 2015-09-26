
#include "Definitions.h"

#include "Logger.h"
using namespace Environment;

#include "CurrentTime.h"
#include <algorithm>

Logger::Logger(DialogueInterface* InTarget, Severity InMinimalSeverity)
	:
	Target(InTarget),
	MinimalSeverity(InMinimalSeverity),
	bWhiteListProjects(false),
	SpecialProjectNames{}
{}

void Logger::SetMinimalSeverity(Severity InMinimalSeverity)
{
	MinimalSeverity = InMinimalSeverity;
}

void Environment::Logger::SetDialogue(DialogueInterface * InTarget)
{
	Target = InTarget;
}

void Logger::Log(const std::string& InMessage, Severity InMessageSeverity, const std::string& InProjectName)
{
	if (InMessageSeverity >= MinimalSeverity)
	{
		bool bProjectIsSpecial = std::find(SpecialProjectNames.begin(), SpecialProjectNames.end(), InProjectName) != SpecialProjectNames.end();
		if (bWhiteListProjects && bProjectIsSpecial || !bWhiteListProjects && !bProjectIsSpecial)
		{
			Target->WriteLine("[" + CurrentTime::ToString() + "] [" + SeverityText::Get((int)InMessageSeverity) + "] " + InProjectName + ": " + InMessage);
		}
	}
}
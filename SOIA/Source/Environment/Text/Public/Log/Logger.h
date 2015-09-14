
#pragma once

#include "DialogueInterface.h"

#include <sstream>

namespace Environment
{
	
	class LIBIMPEXP Logger
	{
	public:
		enum class Severity : int
		{
			DebugInfo = 0,
			Status = 1,
			Warning = 2,
			Error = 3,
			FatalError = 4
		};

		struct SeverityText
		{
			static std::string Get(int Num)
			{
				switch (Num)
				{
				case 0: return "DebugInfo"; break;
				case 1: return "Status"; break;
				case 2: return "Warning"; break;
				case 3: return "Error"; break;
				case 4: return "FatalError"; break;
				}
			}
		};

	public:
		Logger(DialogueInterface* InTarget, Severity InMinimalSeverity = Severity::Status);

		void SetMinimalSeverity(Severity InMinimalSeverity);

		void Log(const std::string& InMessage, Severity InMessageSeverity = Severity::Status, const std::string& InProjectName = PROJECTNAME_LITERAL);

		template<typename T>
		static std::string ToString(T const & InObject)
		{
			std::ostringstream ostrstr;
			ostrstr << InObject;
			return ostrstr.str();
		}

	private:
		DialogueInterface* Target;
		Severity MinimalSeverity;
		bool bWhiteListProjects;	/// if false, then black listing projects
		std::vector<std::string> SpecialProjectNames;
	};
}
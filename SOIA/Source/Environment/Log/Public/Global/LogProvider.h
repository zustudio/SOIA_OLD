
#pragma once

#include "Definitions.h"

#include "Logger.h"

namespace Environment
{
	extern LIBIMPEXP Logger* GetLogger();
#define LOG(message,severity) GetLogger()->Log(message,severity)
#define LOGSTATUS(message) LOG(message,Logger::Severity::Status)
}
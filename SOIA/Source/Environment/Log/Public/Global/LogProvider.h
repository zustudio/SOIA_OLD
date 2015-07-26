
#pragma once

#include "Definitions.h"

#include "Logger.h"

namespace Environment
{
	extern LIBIMPEXP Logger* GlobalLogger();
	extern LIBIMPEXP void SetGlobalLogger(Logger const& InLogger);
#define LOG(message,severity) GlobalLogger()->Log(message,severity)
#define LOGSTATUS(message) LOG(message,Logger::Severity::Status)
}
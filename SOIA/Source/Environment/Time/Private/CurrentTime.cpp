
#include "Definitions.h"

#include "CurrentTime.h"
using namespace Environment;

#include <time.h>
#include <stdio.h>

std::string CurrentTime::ToString()
{
	return GetTimeString();
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string CurrentTime::GetTimeString()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}
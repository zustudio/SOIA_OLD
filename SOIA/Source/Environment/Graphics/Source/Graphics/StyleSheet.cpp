
#include "Definitions.h"

#include "StyleSheet.h"
using namespace Environment;

StyleSheet::StyleSheet(fColor InBackground, TextStyle InHeading, TextStyle InContent)
	:
	Background(InBackground),
	Heading(InHeading),
	Content(InContent)
{}
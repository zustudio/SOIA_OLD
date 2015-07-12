
#include "Definitions.h"

#include "TokenCollapseNone.h"
using namespace Environment;

bool TokenCollapseNone::Collapse(const Iterators<std::vector<Token*>>& InIters)
{
	return true;
}

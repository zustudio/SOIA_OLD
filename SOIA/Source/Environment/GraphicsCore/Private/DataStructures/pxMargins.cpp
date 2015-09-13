
#include "Definitions.h"

#include "pxMargins.h"
using namespace Environment;

pxMargins::pxMargins()
	:
	Left(0),
	Top(0),
	Right(0),
	Bottom(0)
{}

pxMargins::pxMargins(pxMargin InLeft, pxMargin InTop, pxMargin InRight, pxMargin InBottom)
	:
	Left(InLeft),
	Top(InTop),
	Right(InRight),
	Bottom(InBottom)
{}

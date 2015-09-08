
#include "Definitions.h"

#include "ControlWindow.h"
using namespace Environment;

#include "FreeTypeProvider.h"
#include "FileSystemProvider.h"

ControlWindow::ControlWindow(std::string Name, pxSize InSize)
	: GraphicsWindow(Name, InSize),
	CommonTextContentLayer(TextLayer(*GetFont(GetFileSystem()->GetExecutableDirectory().GetPath().AppendFolder("Ressources").AppendFolder("Fonts").AppendFolder("DengXian").AppendFile("DengXian.ttf").ToString()), 15))
{
	AddLayer(&CommonTextContentLayer);
}

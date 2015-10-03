
#include "FreeTypeProvider.h"
#include "StyleSheet.h"
#include "FileSystemProvider.h"

namespace Environment
{
	StyleSheet* CurrentStyle;
	LIBIMPEXP StyleSheet& GlobalStyle()
	{
		if (!CurrentStyle)
		{
			Path path = Path("");
			GetFileSystem()->GetAccess()->GetExecutablePath(path);
			path = path.StripDotName().AppendFolder("Resources").AppendFolder("Fonts").AppendFolder("Raleway").AppendFile("Raleway-Regular.ttf");
			Font* font = GetFont(path.ToString());
			TextStyle headings = TextStyle(font, 30, fColor(0, 0, 0));
			TextStyle content = TextStyle(font, 14, fColor(0, 0, 0));
			CurrentStyle = new StyleSheet(fColor(0.5, 0, 0), headings, content);
		}
		return *CurrentStyle;
	}
}

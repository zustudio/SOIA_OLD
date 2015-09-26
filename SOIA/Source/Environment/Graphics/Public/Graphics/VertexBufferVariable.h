
#pragma once

#include "OpenGLForwardDefinitions.h"

#include <string>

namespace Environment
{
	class VertexBuffer;
	class VertexBufferVariable
	{
	public:
		GLint GLVariable;
		VertexBuffer* Buffer;
		std::string Name;
		int Size;
		int Offset;
	};
}
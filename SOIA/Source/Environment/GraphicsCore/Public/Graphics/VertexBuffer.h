
#pragma once

#include "OpenGLForwardDefinitions.h"

#include "VertexBufferVariable.h"

#include <vector>

namespace Environment
{
	enum class BufferStatus : int
	{
		Idle,
		AwaitingBufferUpdate
	};
	class LIBIMPEXP VertexBuffer
	{
	public:
		VertexBuffer();
		void Initialize();

		/// to be called from an thread - signaling draw request
		void RequestBufferUpdate();

		/// to be called from drawing thread
		bool Update();

		/// generates variable
		virtual VertexBufferVariable CreateVariable(int Index, const std::string& InName) = 0;

		// helpers
		virtual size_t GetRawSize() = 0;
		virtual size_t GetEntrySize() = 0;

	protected:
		bool ResizeFrontBuffer();
		virtual bool SwitchBuffers() = 0;
		bool LoadGLBuffer();


	protected:
		BufferStatus Status;
		std::vector<float> FrontBuffer;
		GLuint GLBuffer;
	};
}

#pragma once

#include "OpenGLForwardDefinitions.h"

#include "VertexBufferVariable.h"

#include <vector>

namespace Environment
{
	enum class VertexBufferType : int
	{
		Vertices,
		Elements
	};
	enum class BufferStatus : int
	{
		Idle,
		AwaitingBufferUpdate
	};
	class LIBIMPEXP VertexBuffer
	{
	public:
		VertexBuffer(VertexBufferType InBufferType);
		void Initialize();

		/// to be called from an thread - signaling draw request
		void RequestBufferUpdate();

		/// to be called from drawing thread
		bool Update();

		/// generates variable
		virtual VertexBufferVariable CreateVariable(int Index, const std::string& InName) = 0;

		// helpers
		bool IsElementBuffer();
		virtual size_t GetRawSize() = 0;
		virtual size_t GetEntrySize() = 0;

	protected:
		virtual void BindBuffer() = 0;
		virtual bool ResizeFrontBuffer() = 0;
		virtual bool SwitchBuffers() = 0;
		virtual bool LoadGLBuffer() = 0;


	protected:
		BufferStatus Status;
		GLuint GLBuffer;
		GLenum GLBufferType;
	};
}
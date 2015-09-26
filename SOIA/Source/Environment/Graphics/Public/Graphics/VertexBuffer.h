
#pragma once

#include "OpenGLForwardDefinitions.h"

#include "VertexBufferVariable.h"
#include "Range.h"

#include <vector>

namespace Environment
{
	enum class VertexBufferType : int
	{
		Vertices,
		Elements
	};
	enum class BufferContentType : int
	{
		Points,
		Lines,
		Triangles,
		TriangleStrip
	};
	enum class BufferStatus : int
	{
		Idle,
		AwaitingBufferUpdate
	};
	class LIBIMPEXP VertexBuffer
	{
	public:
		VertexBuffer(VertexBufferType InBufferType, BufferContentType InContentType);
		void Initialize();

		virtual void EraseRange(Range<int> InRange) = 0;

		/// to be called from an thread - signaling draw request
		void RequestBufferUpdate();

		/// to be called from drawing thread
		bool Update();

		/// generates variable
		virtual VertexBufferVariable CreateVariable(int Index, const std::string& InName) = 0;

		// helpers
		GLenum GetGLBufferType();
		GLenum GetGLContentType();
		
		bool IsBufferType(const VertexBufferType&);
		virtual size_t GetEntryNum() = 0;
		virtual size_t GetRawSize() = 0;
		virtual size_t GetEntrySize() = 0;

	protected:
		static GLenum GenerateGLBufferType(const VertexBufferType&);
		static GLenum GenerateGLContentType(const BufferContentType&);

		virtual void BindBuffer() = 0;
		virtual bool ResizeFrontBuffer() = 0;
		virtual bool SwitchBuffers() = 0;
		virtual bool LoadGLBuffer() = 0;


	protected:
		BufferStatus Status;
		GLuint GLBuffer;
		GLenum GLBufferType;
		GLenum GLContentType;
	};
}
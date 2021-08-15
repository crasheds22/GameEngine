#ifndef OPENGL_BUFFER_H
#define OPENGL_BUFFER_H

#include "Engine/Renderer/Buffer.h"

namespace Engine {

	class OpenGLVertexBuffer
		: public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

	private:
		uint32_t mRendererID;
	};

	class OpenGLIndexBuffer
		: public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual uint32_t Count() const override { return mCount; }

	private:
		uint32_t mRendererID;
		uint32_t mCount;
	};
}

#endif

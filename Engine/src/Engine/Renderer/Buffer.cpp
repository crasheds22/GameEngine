#include "ngpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Engine {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::Get())
		{
		case RendererAPI::API::None: 
			NG_CORE_ASSERT(false, "RendererAPI::None not supported")
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		NG_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::Get())
		{
		case RendererAPI::API::None:
			NG_CORE_ASSERT(false, "RendererAPI::None not supported")
				return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}

		NG_CORE_ASSERT(false, "Unknown RenderAPI");
		return nullptr;
	}
}

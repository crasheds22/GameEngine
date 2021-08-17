#include "ngpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Engine {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::Get())
		{
		case RendererAPI::None: NG_CORE_ASSERT(false, "RendererAPI::None is currently not supported"); return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		NG_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}

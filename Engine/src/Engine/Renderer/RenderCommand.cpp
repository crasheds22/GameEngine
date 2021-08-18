#include "ngpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Engine {

	RendererAPI* RenderCommand::sRendererAPI = new OpenGLRendererAPI;
}

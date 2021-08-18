#include "ngpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Engine {
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRendererAPI::ClearColour(const glm::vec4& colour)
	{
		glClearColor(colour.r, colour.g, colour.b, colour.a);
	}

	void OpenGLRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->Count(), GL_UNSIGNED_INT, nullptr);
	}
}

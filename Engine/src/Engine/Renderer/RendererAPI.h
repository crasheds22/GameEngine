#ifndef RENDERER_API_H
#define RENDERER_API_H

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Engine {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

		virtual void Clear() = 0;
		virtual void ClearColour(const glm::vec4& colour) = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return sAPI; }

	private:
		static API sAPI;
	};
}

#endif // #define RENDERER_API_H

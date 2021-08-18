#pragma once

#include "Engine/Renderer/RendererAPI.h"

namespace Engine {
	
	class OpenGLRendererAPI
		: public RendererAPI
	{
	public:
		void Clear() override;
		void ClearColour(const glm::vec4& colour) override;

		void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;

	};
}

#pragma once

#include "RendererAPI.h"

namespace Engine {

	class RenderCommand
	{
	public:
		static void ClearColour(const glm::vec4& colour) { sRendererAPI->ClearColour(colour); }
		static void Clear() { sRendererAPI->Clear(); }
		static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { sRendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* sRendererAPI;
	};
}

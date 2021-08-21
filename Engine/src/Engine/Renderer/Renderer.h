#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace Engine {

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		static RendererAPI::API Get() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 ViewProjection;
		};

		static SceneData* sSceneData;
	};
}

#include "ngpch.h"
#include "Renderer.h"

namespace Engine {

	Renderer::SceneData* Renderer::sSceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		sSceneData->ViewProjection = camera.ViewProjection();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

}

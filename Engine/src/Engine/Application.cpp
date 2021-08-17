#include "ngpch.h"
#include "Application.h"

#include "Engine/Log.h"

#include <glad/glad.h>

#include "Input.h"

namespace Engine {

	Application* Application::sInstance = nullptr;

	Application::Application()
	{
		NG_CORE_ASSERT(!sInstance, "Application already exists");
		sInstance = this;

		mWindow = std::unique_ptr<Window>(Window::Create());
		mWindow->EventCallback(BIND_EVENT_FN(Application::OnEvent));

		mImGuiLayer = new imguiLayer();
		PushOverlay(mImGuiLayer);

		mVertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
			0.0f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "aPosition"},
			{ShaderDataType::Float4, "aColour"}
		};

		vertexBuffer->Layout(layout);
		mVertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		mVertexArray->AddIndexBuffer(indexBuffer);

		std::string vertSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColour;

			out vec3 vPosition;
			out vec4 vColour;

			void main() {
				vPosition = aPosition;
				vColour = aColour;
				gl_Position = vec4(aPosition, 1.0);
			}
		)";

		std::string fragSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 colour;

			in vec3 vPosition;
			in vec4 vColour;

			void main() {
				colour = vColour;
			}
		)";

		mShader.reset(new Shader(vertSrc, fragSrc));
	}

	void Application::Run()
	{
		while (mRunning)
		{
			glClearColor(0.5f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			mShader->Bind();

			mVertexArray->Bind();
			glDrawElements(GL_TRIANGLES, mVertexArray->GetIndexBuffer()->Count(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : mLayerStack)
				layer->OnUpdate();

			mImGuiLayer->Begin();
			for (Layer* layer : mLayerStack)
				layer->OnImGuiRender();
			mImGuiLayer->End();

			mWindow->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = mLayerStack.end(); it != mLayerStack.begin(); )
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		mLayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		mLayerStack.PushOverlay(layer);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		mRunning = false;
		return true;
	}

}

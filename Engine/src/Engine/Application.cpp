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

		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);

		float vertices[3 * 3] = {
			-0.5, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		mVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);


		uint32_t indices[3] = { 0, 1, 2 };

		mIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 aPosition;

			out vec3 vPosition;

			void main() {
				vPosition = aPosition;
				gl_Position = vec4(aPosition, 1.0);
			}
		)";

		std::string fragSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 vPosition;

			void main() {
				color = vec4(vPosition * 0.5 + 0.5, 1.0);
			}
		)";

		mShader.reset(new Shader(vertSrc, fragSrc));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (mRunning)
		{
			glClearColor(0.5f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			mShader->Bind();

			glBindVertexArray(mVAO);
			glDrawElements(GL_TRIANGLES, mIndexBuffer->Count(), GL_UNSIGNED_INT, nullptr);

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

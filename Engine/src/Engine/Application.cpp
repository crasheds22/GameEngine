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
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (mRunning)
		{
			glClearColor(0.5, 0.2, 0.2, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);

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
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		mLayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		mRunning = false;
		return true;
	}

}

#pragma once

#include "Core.h"

#include "Window.h"

#include "Engine/LayerStack.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Engine/imgui/imguiLayer.h"

#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/VertexArray.h"

#include "Engine/Renderer/OrthographicCamera.h"

namespace Engine {

	class ENGINE_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *mWindow; }

		static Application& Get() { return *sInstance; }

	private:
		bool OnWindowClose(WindowCloseEvent& event);

		std::unique_ptr<Window> mWindow;
		imguiLayer* mImGuiLayer;

		bool mRunning = true;

		LayerStack mLayerStack;

		std::shared_ptr<Shader> mShader;
		std::shared_ptr<VertexArray> mVertexArray;

		OrthographicCamera mCamera;

		static Application* sInstance;
	};

	Application* CreateApplication();
}

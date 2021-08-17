#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core.h"

#include "Window.h"

#include "Engine/LayerStack.h"
#include "Engine/Events/Event.h"
#include "Engine/Events/ApplicationEvent.h"

#include "Engine/imgui/imguiLayer.h"

#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/Buffer.h"
#include "Engine/Renderer/VertexArray.h"

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

		std::unique_ptr<Shader> mShader;
		std::unique_ptr<VertexArray> mVertexArray;

		static Application* sInstance;
	};

	Application* CreateApplication();
}

#endif

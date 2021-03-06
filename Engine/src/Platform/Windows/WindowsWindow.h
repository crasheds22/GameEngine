#pragma once

#include "Engine/Window.h"

#include "Engine/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/MouseEvent.h"
#include "Engine/Events/KeyEvent.h"

namespace Engine {

	class WindowsWindow
		: public Window
	{
	public:
		WindowsWindow(const WindowProps& prop);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int Width() const override { return mData.Width; }
		unsigned int Height() const override { return mData.Height; }

		void EventCallback(const EventCallbackFn& callback) override { mData.EventCallback = callback; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		
		virtual void* NativeWindow() const override;

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* mWindow;
		GraphicsContext* mContext;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData mData;
	};
}

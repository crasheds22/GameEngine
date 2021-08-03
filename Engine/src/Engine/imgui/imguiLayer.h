#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "Engine/Layer.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Engine/Events/KeyEvent.h"
#include "Engine/Events/MouseEvent.h"

namespace Engine {

	class ENGINE_API imguiLayer
		: public Layer
	{
	public:
		imguiLayer();
		~imguiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);

		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleaseEvent& event);

		bool OnWindowResizedEvent(WindowResizeEvent& event);

	private:
		float mTime = 0.0f;
	};
}

#endif

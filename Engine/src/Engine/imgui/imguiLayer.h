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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float mTime = 0.0f;
	};
}

#endif

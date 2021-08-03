#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include "Engine/Layer.h"

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
	};
}

#endif

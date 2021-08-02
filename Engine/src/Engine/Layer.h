#ifndef LAYER_H
#define LAYER_H

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace Engine {

	class ENGINE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		const std::string& Name() const { return mDebugName; }

	protected:
		std::string mDebugName;
	};
}

#endif

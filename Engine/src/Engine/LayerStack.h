#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include "Engine/Core.h"
#include "Layer.h"

#include <vector>

namespace Engine {

	class ENGINE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<Layer*>::iterator begin() { return mLayers.begin(); }
		std::vector<Layer*>::iterator end() { return mLayers.end(); }

	private:
		std::vector<Layer*> mLayers;
		std::vector<Layer*>::iterator mLayerInsert;
	};
}

#endif
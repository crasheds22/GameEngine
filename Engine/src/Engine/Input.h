#ifndef INPUT_H
#define INPUT_H

#include "Engine/Core.h"

namespace Engine {

	class ENGINE_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return sInstance->iIsKeyPressed(keycode); }
		static bool IsMouseButtonPressed(int button) { return sInstance->iIsMouseButtonPressed(button); }
		static std::pair<float, float> MousePos() { return sInstance->iMousePos(); }

		static float MouseX() { return MousePos().first; }
		static float MouseY() { return MousePos().second; }

	protected:
		virtual bool iIsKeyPressed(int keycode) = 0;
		virtual bool iIsMouseButtonPressed(int button) = 0;
		virtual std::pair<float, float> iMousePos() = 0;

	private:
		static Input* sInstance;
	};
}

#endif

#ifndef WINDOWS_INPUT_H
#define WINDOWS_INPUT_H

#include "Engine/Input.h"

namespace Engine {

	class WindowsInput
		: public Input
	{
	protected:
		virtual bool iIsKeyPressed(int keycode) override;

		virtual bool iIsMouseButtonPressed(int button) override;

		virtual std::pair<float, float> iMousePos() override;

	};
}

#endif

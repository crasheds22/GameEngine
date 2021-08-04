#include "ngpch.h"
#include "WindowsInput.h"

#include "Engine/Application.h"
#include <GLFW/glfw3.h>

namespace Engine {

	Input* Input::sInstance = new WindowsInput();

	bool WindowsInput::iIsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().NativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::iIsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().NativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::iMousePos()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().NativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}
}

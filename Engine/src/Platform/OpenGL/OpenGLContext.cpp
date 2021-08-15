#include "ngpch.h"
#include "OpenGLContext.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Engine {
	
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: mWindowHandle(windowHandle)
	{
		NG_CORE_ASSERT(mWindowHandle, "Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(mWindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NG_CORE_ASSERT(status, "Failed to init GLAD");

		NG_CORE_INFO("OpenGL Info:");
		NG_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		NG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		NG_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(mWindowHandle);
	}
}

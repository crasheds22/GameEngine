#include "ngpch.h"
#include "WindowsWindow.h"

namespace Engine {

    static bool sGLFWInitialized = false;

    Window* Window::Create(const WindowProps& prop)
    {
        return new WindowsWindow(prop);
    }

    Engine::WindowsWindow::WindowsWindow(const WindowProps& prop)
    {
        Init(prop);
    }

    Engine::WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void Engine::WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(mWindow);
    }

    void Engine::WindowsWindow::SetVSync(bool enabled)
    {
        if (enabled)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        mData.VSync = enabled;
    }

    bool Engine::WindowsWindow::IsVSync() const
    {
        return mData.VSync;
    }

    void Engine::WindowsWindow::Init(const WindowProps& props)
    {
        mData.Title = props.Title;
        mData.Width = props.Width;
        mData.Height = props.Height;

        NG_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!sGLFWInitialized)
        {
            int success = glfwInit();
            NG_CORE_ASSERT(success, "Could not initialize GLFW");

            sGLFWInitialized = true;
        }

        mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, mData.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(mWindow);
        glfwSetWindowUserPointer(mWindow, &mData);
        SetVSync(true);
    }

    void Engine::WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(mWindow);
    }
}

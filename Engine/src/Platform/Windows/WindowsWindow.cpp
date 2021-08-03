#include "ngpch.h"
#include "WindowsWindow.h"

namespace Engine {

    static bool sGLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description)
    {
        NG_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

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
            glfwSetErrorCallback(GLFWErrorCallback);

            sGLFWInitialized = true;
        }

        mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, mData.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(mWindow);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        NG_CORE_ASSERT(status, "Failed to initialize GLAD");
        
        glfwSetWindowUserPointer(mWindow, &mData);
        SetVSync(true);

        glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            data.Width = width;
            data.Height = height;
            
            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });

        glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mod) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleaseEvent event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    data.EventCallback(event);
                    break;
                }
                default:
                    break;
            }
        });

        glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.EventCallback(event);
                    break;
                }
                default:
                    break;
            }
        });

        glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

        glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int keycode) {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });
    }

    void Engine::WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(mWindow);
    }
}

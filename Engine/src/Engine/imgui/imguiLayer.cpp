#include "ngpch.h"
#include "imguiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"

#include "Engine/Application.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {

	imguiLayer::imguiLayer()
		: Layer("ImGui")
	{
	}

	imguiLayer::~imguiLayer()
	{
	}

	void imguiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Engine key codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void imguiLayer::OnUpdate()
	{
		ImGuiIO& imguiIO = ImGui::GetIO();
		Application& app = Application::Get();
		imguiIO.DisplaySize = ImVec2(app.GetWindow().Width(), app.GetWindow().Height());

		float time = (float)glfwGetTime();
		imguiIO.DeltaTime = mTime > 0.0f ? (time - mTime) : (1.0f / 60.0f);
		mTime = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void imguiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(imguiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FN(imguiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FN(imguiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FN(imguiLayer::OnMouseMovedEvent));

		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(imguiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleaseEvent>(BIND_EVENT_FN(imguiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FN(imguiLayer::OnKeyTypedEvent));

		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(imguiLayer::OnWindowResizedEvent));
	}

	void imguiLayer::OnDetach()
	{
	}

	bool imguiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseDown[event.GetMouseButton()] = true;

		return false;
	}

	bool imguiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseDown[event.GetMouseButton()] = false;

		return false;

	}

	bool imguiLayer::OnMouseMovedEvent(MouseMovedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MousePos = ImVec2(event.X(), event.Y());

		return false;

	}

	bool imguiLayer::OnMouseScrolledEvent(MouseScrolledEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseWheelH += event.XOffset();
		io.MouseWheel += event.YOffset();

		return false;

	}

	bool imguiLayer::OnKeyTypedEvent(KeyTypedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		if (event.KeyCode() > 0 && event.KeyCode() < 0x10000)
			io.AddInputCharacter((unsigned short)event.KeyCode());

		return false;
	}

	bool imguiLayer::OnKeyPressedEvent(KeyPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[event.KeyCode()] = true;

		io.KeyCtrl		= io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift		= io.KeysDown[GLFW_KEY_LEFT_SHIFT]	|| io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt		= io.KeysDown[GLFW_KEY_LEFT_ALT]	|| io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper		= io.KeysDown[GLFW_KEY_LEFT_SUPER]	|| io.KeysDown[GLFW_KEY_RIGHT_SUPER];

		return false;
	}

	bool imguiLayer::OnKeyReleasedEvent(KeyReleaseEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[event.KeyCode()] = false;

		return false;
	}

	bool imguiLayer::OnWindowResizedEvent(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(event.Width(), event.Height());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

		glViewport(0, 0, event.Width(), event.Height());

		return false;
	}
}

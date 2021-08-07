
#include <Engine.h>

class ExampleLayer
	: public Engine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	virtual void OnUpdate() override
	{
		//NG_INFO("ExampleLayer::Update");
	}

	virtual void OnImGuiRender() override
	{
	}

	virtual void OnEvent(Engine::Event& event) override
	{
		//NG_TRACE("{0}", event);
	}
};

class Sandbox : public Engine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Engine::Application* Engine::CreateApplication()
{
	return new Sandbox();
}

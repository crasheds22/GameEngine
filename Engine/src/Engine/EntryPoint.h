#pragma once

#ifdef NG_PLATFORM_WINDOWS

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
	Engine::Log::Init();
	NG_CORE_WARN("initialized");
	NG_INFO("Hello there");

	auto app = Engine::CreateApplication();

	app->Run();

	delete app;
}

#endif

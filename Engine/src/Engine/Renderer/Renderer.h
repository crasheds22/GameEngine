#ifndef RENDERER_H
#define RENDERER_H

namespace Engine {

	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		static RendererAPI Get() { return sRendererAPI; }

	private:
		static RendererAPI sRendererAPI;
	};
}

#endif

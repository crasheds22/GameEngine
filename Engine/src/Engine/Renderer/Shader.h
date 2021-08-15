#ifndef SHADER_H
#define SHADER_H

#include <string>

namespace Engine {

	class Shader
	{
	public:
		Shader(const std::string& vertSrc, const std::string& fragSrc);
		~Shader();

		void Bind() const;
		void unbind() const;

	private:
		uint32_t mRendererID;

	};
}
#endif

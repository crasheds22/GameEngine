#ifndef SHADER_H
#define SHADER_H

#include <string>
// TODO: Fuckin fix this shit
#include <../Vendor/glm/glm/glm.hpp>

namespace Engine {

	class Shader
	{
	public:
		Shader(const std::string& vertSrc, const std::string& fragSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void Uniform(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t mRendererID = 0;

	};
}
#endif

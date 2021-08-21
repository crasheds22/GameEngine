#pragma once

#include <string>
<<<<<<< HEAD
#include <glm/glm.hpp>
=======
// TODO: Fuckin fix this shit
#include <../Vendor/glm/glm/glm.hpp>
>>>>>>> main

namespace Engine {

	class Shader
	{
	public:
		Shader(const std::string& vertSrc, const std::string& fragSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void Uniform(const std::string& name, const glm::mat4& matrix);
<<<<<<< HEAD
=======

>>>>>>> main
	private:
		uint32_t mRendererID = 0;

	};
}

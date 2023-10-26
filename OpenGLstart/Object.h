#pragma once
#include <string>
#include "glew.h"
#include <iostream> 

#include "glm/glm.hpp"



namespace OpenGLENG {
	class Object {
	private:
		GLuint coords_vbo;
		GLuint colors_vbo;
		GLuint vao;
		GLuint pointn;
		Object(std::string filename, glm::vec3 color);
	public:
		static Object* LoadFromOBJ(std::string filename, glm::vec3 color);
		void draw(glm::mat4 transrormMatrix, GLuint shader_programme);
		~Object();
	};
}


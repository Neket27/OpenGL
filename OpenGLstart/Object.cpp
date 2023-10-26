#include "Object.h"
#include "OBJloader.h" 
#include <fstream>
namespace OpenGLENG {
	Object::Object(std::string filename,glm::vec3 color) {
		std::vector<glm::vec3> points;
		std::vector<glm::vec2> outTextures;
		std::vector<glm::vec3> outNormals;
		OBJLoad(filename.c_str(), points, outTextures, outNormals);
		std::vector<glm::vec3> colors;
		pointn = points.size();
		for (int i = 0; i < pointn; i++)
			colors.push_back(color);
		coords_vbo = 0;
	    glGenBuffers(1, &coords_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
		glBufferData(GL_ARRAY_BUFFER, pointn * 3 * sizeof(GLfloat), &points[0], GL_STATIC_DRAW);
		colors_vbo = 0;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, pointn * 3 * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
	    vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
	}

	Object* Object::LoadFromOBJ(std::string filename, glm::vec3 color)
	{
		return new Object(filename,color);
	}

	void Object::draw(glm::mat4 transrormMatrix, GLuint shader_programme)
	{
		GLuint stm = glGetUniformLocation(shader_programme, "transform");
		glUniformMatrix4fv(stm, 1, GL_FALSE, &transrormMatrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, pointn);
	}

	Object::~Object() {
		glDeleteBuffers(1, &coords_vbo);
		glDeleteBuffers(1, &colors_vbo);
		glDeleteBuffers(1, &vao);
	}
}
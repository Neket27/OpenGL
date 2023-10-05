#include "glew.h" // подключение GLEW
#include <GLFW/glfw3.h> 
#include <iostream> 
#include "ShaderFuncs.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
int WinWidth = 640;
int WinHeight = 480;

void drawSmth(GLuint stm, GLuint shader_programme);
void glfw_window_size_callback(GLFWwindow* window, int width, int height);

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WinWidth, WinHeight, "Triangle",
		NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSetWindowSizeCallback(window, glfw_window_size_callback);
	GLuint vs = LoadShader("VertexShader.glsl", GL_VERTEX_SHADER);
	GLuint fs = LoadShader("FragmentShader.glsl", GL_FRAGMENT_SHADER);
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, vs);
	glAttachShader(shader_programme, fs);
	glBindAttribLocation(shader_programme, 0, "vertex_position");
	glBindAttribLocation(shader_programme, 1, "vertex_colour");
	glLinkProgram(shader_programme);


	GLuint stm = glGetUniformLocation(shader_programme, "transform");

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, 1);
		}
		glViewport(0, 0, WinWidth, WinHeight);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_programme);
		//drawHexagonDots(-0.75f, 0.75f, 0.2f);
		drawSmth(stm,shader_programme);

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}


void glfw_window_size_callback(GLFWwindow* window, int width, int
	height) {
	WinWidth = width;
	WinHeight = height;
}
void drawSmth(GLuint stm, GLuint shader_programme) {
	glm::vec3 points[] = {
{0.0f, 0.5f, 0.0f},
{0.5f, 0.0f, 0.0f},
{0.0f, -0.5f, 0.0f},
{-0.5f, 0.0f, 0.0f}
	};
	glm::vec3 colors[] = {
	{1.0f, 0.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 1.0f},
	{1.0f, 1.0f, 0.0f}
	};
	//GLuint indices[] = { 0, 1, 2 };
	GLuint indices[] = { 0, 1, 2, 2, 3, 0 }; // обход вершин

	glm::mat4 transformMatrix = glm::mat4(1.0f);
	
		glUniformMatrix4fv(stm, 1, GL_FALSE, &transformMatrix[0][0]);
		GLuint coords_vbo = 0;
		glGenBuffers(1, &coords_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points,
			GL_STATIC_DRAW);
		GLuint colors_vbo = 0;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors),
			colors, GL_STATIC_DRAW);
		GLuint elementbuffer;
		glGenBuffers(1, &elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		GLuint vao = 0;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint),
			GL_UNSIGNED_INT, 0);
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &coords_vbo);
		glDeleteBuffers(1, &colors_vbo);
		glDeleteBuffers(1, &elementbuffer);

}















void drawHexagonDots(GLfloat startx, GLfloat starty, GLfloat size) {
	//GLfloat colors[] = {
	//	 0.0f, 0.5f, 0.0f,
	//	 0.0f, 0.5f, 0.0f,
	//	 0.0f, 0.5f, 0.0f,
	//	 0.0f, 0.5f, 0.0f,
	//	 0.0f, 0.5f, 0.0f,
	//	 0.0f, 0.5f, 0.0f,
	//};
	//GLfloat points[] = {
	//   0.0f, 1.0f, 0.0f,
	//  -0.86f, 0.5f, 0.0f,
	//   0.86f, 0.5f, 0.0f,
	//   0.86f, -0.5f, 0.0f,
	//   -0.86f, -0.5f, 0.0f,
	//   0.0f, -1.0f, 0.0f
	//};







	//drawSmth(colors, points, startx, starty, size, GL_POINTS, 6);
}


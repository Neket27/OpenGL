#include "glew.h" // подключение GLEW
#include <glfw3.h> 
#include <iostream> 
#include "ShaderFuncs.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

struct dataPoint {
	std::vector<glm::vec3> coordinates;
	std::vector<glm::vec3>  colors;
	size_t sizeDataPoints;

	void addCoordinates(glm::vec3 coordinate) {
		coordinates.push_back(coordinate);
		sizeDataPoints= (coordinates.size()) == 0 ? 0 : 3 * coordinates.size();
	}

	void addColors(glm::vec3 color) {
		colors.push_back(color);
	}
	// Метод для получения указателя на данные координат
	glm::vec3* getCoordinatesData() {
		return coordinates.data();
	}

	// Метод для получения указателя на данные цветов
	glm::vec3* getColorsData() {
		return colors.data();
	}


};


int WinWidth = 640;
int WinHeight = 480;

void glfw_window_size_callback(GLFWwindow* window, int width, int height);
void drawSmth(dataPoint dataPoints, std::vector<GLuint> indexes, glm::mat4 transformMatrix, GLuint shader_programme, GLenum type);
void task1(GLuint shader_programme);
void ff(GLint shader_programme);

int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WinWidth, WinHeight, "Triangle", NULL, NULL);
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
		ff(shader_programme);
		//task1(shader_programme);


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



void drawSmth(dataPoint dataPoints, std::vector<GLuint> indexes, glm::mat4 transformMatrix, GLuint shader_programme, GLenum type) {
	GLuint stm = glGetUniformLocation(shader_programme, "transform");	
	glUniformMatrix4fv(stm, 1, GL_FALSE, &transformMatrix[0][0]);

	//БУФЕРЫ
	GLuint coords_vbo = 0;
	glGenBuffers(1, &coords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glBufferData(GL_ARRAY_BUFFER,  dataPoints.sizeDataPoints * sizeof(GLfloat), dataPoints.getCoordinatesData(), GL_STATIC_DRAW);
	
	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, dataPoints.sizeDataPoints * sizeof(GLfloat),dataPoints.getColorsData(), GL_STATIC_DRAW);
	
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(GLuint), indexes.data(), GL_STATIC_DRAW);
	// end БУФЕРЫ

	//Массив
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
	// end массивы

	//Отрисовка
	glDrawElements(type, indexes.size(), GL_UNSIGNED_INT, 0);
	// end Отрисовка


	//Освобождение памяти
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &coords_vbo);
	glDeleteBuffers(1, &colors_vbo);
	glDeleteBuffers(1, &elementbuffer);
	// end Освобождение памяти
}




void ff(GLint shader_programme) {
	std::vector<GLuint> indexes = { 0, 1, 2, 2, 3, 0 };

	dataPoint dataPoints;
	dataPoints.addCoordinates({ 0.0f, 0.5f, 0.0f });
	dataPoints.addCoordinates({ 0.5f, 0.0f, 0.0f });
	dataPoints.addCoordinates({ 0.0f, -0.5f, 1.0f });
	dataPoints.addCoordinates({ -0.5f, 0.0f, 0.0f });

	dataPoints.addColors({ 1.0f, 0.0f, 0.0f });
	dataPoints.addColors({ 0.0f, 1.0f, 0.0f });
	dataPoints.addColors({ 0.0f, 0.0f, 1.0f });
	dataPoints.addColors({ 1.0f, 1.0f, 0.0f });

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // отрисовка только граний
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	drawSmth(dataPoints, indexes, transformMatrix, shader_programme, GL_TRIANGLES);


}


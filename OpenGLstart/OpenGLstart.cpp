#include "glew.h" // подключение GLEW
#include <glfw3.h> 
#include <iostream> 
#include "ShaderFuncs.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <vector>


int WinWidth = 640;
int WinHeight = 480;




void drawSmth(glm::vec3 colors[], glm::vec3 points[], GLuint indexes[], glm::mat4 transformMatrix, GLuint shader_programme, GLenum type, int n, int ind);
void glfw_window_size_callback(GLFWwindow* window, int width, int height);
void drawSmth2(glm::vec3 colors[], glm::vec3* ptr, GLuint indexes[], glm::mat4 transformMatrix, GLuint shader_programme, GLenum type, int n, int ind);
void task1(GLuint shader_programme);
void ff(GLint shader_programme);

template <typename T>
struct array
{
	size_t size;
	T data;

};



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

void drawSmth(glm::vec3 colors[], glm::vec3 points[], GLuint indexes[], glm::mat4 transformMatrix, GLuint shader_programme, GLenum type, int n, int ind){

	GLuint stm = glGetUniformLocation(shader_programme, "transform");
		glUniformMatrix4fv(stm, 1, GL_FALSE, &transformMatrix[0][0]);

		//БУФЕРЫ
		GLuint coords_vbo = 0;
		glGenBuffers(1, &coords_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
		glBufferData(GL_ARRAY_BUFFER, 4*3*sizeof(points), points,
			GL_STATIC_DRAW);

		GLuint colors_vbo = 0;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(colors),
			colors, GL_STATIC_DRAW);

		GLuint elementbuffer;
		glGenBuffers(1, &elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		GLuint arr[] = { 1, 2, 3, 4, 5 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(indexes), indexes, GL_STATIC_DRAW);
		// end БУФЕРЫ
		
///////////////////////////////////////////////////////////////////////////////////////////////////

		//Массив
		GLuint vao = 0;
		glGenVertexArrays(1, &vao); //создаёт массив вершин и помещает его идентификатор в переданный параметр
		glBindVertexArray(vao); //устанавливает выбранный массив вершин в качестве текущего
		glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL); //// потом будем включать массив 1 (связывает активный массив вершин с активным буфером и присваивает ему индекс, переданный в качестве первого параметра.)
		
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL); // потом будем включать массив 1

		glEnableVertexAttribArray(0); // включаем массив. (в данном случае характеристика только одна - координаты, так что используется индекс 0)
		glEnableVertexAttribArray(1); //включаем массив. (в данном случае характеристики только две - координаты и цвета, так что используется индекс 1)

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
		// end массивы

		//Отрисовка
		glDrawElements(GL_TRIANGLES, sizeof(indexes) / sizeof(GLuint),GL_UNSIGNED_INT, 0);
		// end Отрисовка

		//Освобождение памяти
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &coords_vbo);
		glDeleteBuffers(1, &colors_vbo);
		glDeleteBuffers(1, &elementbuffer);
		// end Освобождение памяти
}




void drawSmth2(glm::vec3 colors[], glm::vec3* points, GLuint indexes[], glm::mat4 transformMatrix, GLuint shader_programme, GLenum type, int n, int ind) {
	GLuint stm = glGetUniformLocation(shader_programme, "transform");
	glm::vec3 v(2.f, 2.f, 2.f);
	float length = glm::length(v);
	glUniformMatrix4fv(stm, 1, GL_FALSE, &transformMatrix[0][0]);
	GLuint coords_vbo = 0;
	glGenBuffers(1, &coords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glBufferData(GL_ARRAY_BUFFER, n * 3 * sizeof(GLfloat), points, GL_STATIC_DRAW);
	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, n*3 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	GLuint elementbuffer;
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind * sizeof(GLuint), indexes, GL_STATIC_DRAW);
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
	glDrawElements(type, ind, GL_UNSIGNED_INT, 0);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &coords_vbo);
	glDeleteBuffers(1, &colors_vbo);
	glDeleteBuffers(1, &elementbuffer);
}





struct dataPoints {
	glm::vec3 coordinates;
	size_t lenCoordinates=0;
	glm::vec3 colors;
	size_t lenColors;
	GLuint drawingOrder;
	size_t lenDrawingOrder;

	void addCoordinates(glm::vec3 coordinates1) {
	coordinates = coordinates + coordinates1;
	lenCoordinates++;
	}

};





void ff(GLint shader_programme) {

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

	GLuint indexes[] = { 0, 1, 2, 2, 3, 0 }; // обход вершин

	dataPoints dataPoints;
	dataPoints.addCoordinates({ 0.0f, 0.5f, 0.0f });
	dataPoints.addCoordinates({ 0.5f, 0.0f, 0.0f });
	dataPoints.addCoordinates({ 0.0f, -0.5f, 0.0f });
	dataPoints.addCoordinates({ -0.5f, 0.0f, 0.0f });


	//glm::vec3 coordinates[] = dataPoints;

	glm::vec3* ptr = &dataPoints.coordinates;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	drawSmth2(colors, ptr, indexes, transformMatrix, shader_programme, GL_TRIANGLES, 4, 6);


}


void task1(GLuint shader_programme) {
	glm::vec3 points[] = {
		   {-0.1f,0.0f,0.0f},
		   {-0.2f, 0.6f, 0.0f },
		   {-0.3f, 0.0f, 0.0f},
		   {-0.4f, -0.5f, 0.0f},
		   {-0.5f, 0.0f, 0.0f},
		   {-0.6f, -0.7f, 0.0f}

	};
	glm::vec3 colors[] = {
		{1.0f,1.0f,1.0f},
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f},
		{1.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 1.0f}
	};
	GLuint indexes[] = {
					   0,1,2,
					   0,1,3,
					   0,1,4,
					   0,1,5,
					   0,2,3,
					   0,2,4,
					   0,2,5,
					   0,3,4,
					   0,3,5,
					   0,4,5,
					   1,2,3,
					   1,2,4,
					   1,2,5,
					   1,3,4,
					   1,3,5,
					   1,4,5,
					   2,3,4,
					   2,3,5,
	};
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	drawSmth2(colors, points, indexes, transformMatrix, shader_programme, GL_TRIANGLES, 6, 36);
	glm::vec3 points2[] = {
			 {0.1f,0.0f,0.0f},
			 {0.2f, 0.6f, 0.0f },
			 {0.3f, 0.0f, 0.0f},
			 {0.4f, -0.5f, 0.0f},
			 {0.5f, 0.0f, 0.0f},
			 {0.6f, -0.7f, 0.0f}

	};
	glm::vec3 colors2[] = {
		{1.0f,1.0f,1.0f},
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f},
		{1.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 1.0f}
	};
	GLuint indexes2[] = {
				0,1,
				0,2,
				0,3,
				0,4,
				0,5,
				1,2,
				1,3,
				1,4,
				1,5,
				2,3,
				2,4,
				2,5,
				3,4,
				3,5,
				4,5
	};

	transformMatrix = glm::mat4(1.0f);
	drawSmth2(colors2, points2, indexes2, transformMatrix, shader_programme, GL_LINES, 6, 30);
}

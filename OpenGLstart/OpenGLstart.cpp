#include "glew.h"
#include <glfw3.h> 
#include <iostream> 
#include "ShaderFuncs.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "TimerView.cpp"
#include "dataPoint.h"


int WinWidth = 840;
int WinHeight = 580;

GLfloat x=0;
GLfloat y=0;
bool straightOrPerspective = false;
int  numberTask = 0;

void glfw_window_size_callback(GLFWwindow* window, int width, int height);
void drawSmth(dataPoint dataPoints, std::vector<GLuint> indexes, glm::mat4 transformMatrix, GLuint shader_programme, GLenum type);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void task_1And2(GLint shader_programme);
void task_3(GLuint shader_programme);
void task_4(GLuint shader_programme);
void task_5(GLuint shader_programme);
void task_6(GLuint shader_programme);
void drawSmth2(glm::vec3 colors[], glm::vec3 points[], GLuint indexes[], glm::mat4 transformMatrix, GLuint shader_programme, GLenum type, int n, int ind);
void drawCube(GLfloat size, glm::mat4 transformMatrix1, GLuint shader_programme);


int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(WinWidth, WinHeight, "Triangle", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowSizeCallback(window, glfw_window_size_callback);
	GLuint vs = LoadShader("VertexShader.glsl", GL_VERTEX_SHADER);
	GLuint fs = LoadShader("FragmentShader.glsl", GL_FRAGMENT_SHADER);
	GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, vs);
	glAttachShader(shader_programme, fs);
	glBindAttribLocation(shader_programme, 0, "vertex_position");
	glBindAttribLocation(shader_programme, 1, "vertex_colour");
	glLinkProgram(shader_programme);


	glViewport(0, 0, WinWidth, WinHeight);

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(window, 1);
		}
		glViewport(0, 0, WinWidth, WinHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader_programme);

		switch (numberTask) {
		case 0:
			glDepthFunc(GL_LESS);
			task_1And2(shader_programme);
			break;

		case 1:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			task_1And2(shader_programme);
			break;

		case 2:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			task_3(shader_programme);
			break;
		case 3:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			task_4(shader_programme);
			break;
		case 4:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			task_5(shader_programme);
			break;
		case 5:
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			task_6(shader_programme);
			break;
		
	}

		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	else  if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		numberTask = (numberTask++) % 6;
	else  if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
		x -= 1;
	else  if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
		x += 1;
	else  if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
		y -= 1;
	else  if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
		y += 1;
	else  if (key == GLFW_KEY_M && action == GLFW_PRESS)
		straightOrPerspective = !straightOrPerspective;
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
	glBufferData(GL_ARRAY_BUFFER, dataPoints.sizeDataPoints * sizeof(GLfloat), dataPoints.getCoordinatesData(), GL_STATIC_DRAW);

	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, dataPoints.sizeDataPoints * sizeof(GLfloat), dataPoints.getColorsData(), GL_STATIC_DRAW);

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

void task_1And2(GLint shader_programme) {
	std::vector<GLuint> indexes1 = {
					   0,1,3,
					   2,3,1
	};

	dataPoint dataPoints1;
	dataPoints1.addCoordinates({ -0.6f, -0.6f, -0.2f });
	dataPoints1.addCoordinates({ 0.6f, -0.6f, -0.2f });
	dataPoints1.addCoordinates({ 0.6f, 0.6f, -0.2f });
	dataPoints1.addCoordinates({ -0.6f, 0.6f, -0.2f });

	dataPoints1.addColors({ 1.0f, 0.0f, 0.0f });
	dataPoints1.addColors({ 1.0f, 0.0f, 0.0f });
	dataPoints1.addColors({ 1.0f, 0.0f, 0.0f });
	dataPoints1.addColors({ 1.0f, 0.0f, 0.0f });

	glm::mat4 transformMatrix1 = glm::mat4(1.0f);
	drawSmth(dataPoints1, indexes1,transformMatrix1, shader_programme, GL_TRIANGLES);

	dataPoint dataPoints2;
	dataPoints2.addCoordinates({ -0.5f, 0.8f, -0.8f });
	dataPoints2.addCoordinates({ -0.5f, 0.8f, 0.8f });
	dataPoints2.addCoordinates({ -0.5f, -0.8f, 0.8f });
	dataPoints2.addCoordinates({ -0.5f, -0.8f, -0.8f });

	dataPoints2.addColors({ 0.0f,1.0f,0.0f });
	dataPoints2.addColors({ 0.0f,1.0f,0.0f });
	dataPoints2.addColors({ 0.0f,1.0f,0.0f });
	dataPoints2.addColors({ 0.0f,1.0f,0.0f });
	std::vector<GLuint> indexes2 = {
		0,2,1,
		0,2,3
	};

	glm::mat4 transformMatrix2 = glm::mat4(1.0f);
	drawSmth(dataPoints2, indexes2, transformMatrix2, shader_programme, GL_TRIANGLES);


	dataPoint dataPoints3;
	dataPoints3.addCoordinates({ -1.0f, -1.0f, 0.0f });
	dataPoints3.addCoordinates({ 0.0f, 1.0f, 1.0f });
	dataPoints3.addCoordinates({ 1.0f, 0.0f, 0.0f });

	dataPoints3.addColors({ 0.0f,0.0f,1.0f });
	dataPoints3.addColors({ 0.0f,0.0f,1.0f });
	dataPoints3.addColors({ 0.0f,0.0f,1.0f });

	std::vector<GLuint> indexes3 = {0,2,1,};

	glm::mat4 transformMatrix3 = glm::mat4(1.0f);
	drawSmth(dataPoints3, indexes3, transformMatrix3, shader_programme, GL_TRIANGLES);

}

void task_3(GLuint shader_programme) {
	glm::mat4 transformMatrix1 = glm::mat4(1.0f);
	transformMatrix1 = glm::translate(transformMatrix1, { 0.0f,0.0f,-4.0f });
	glm::mat4 projMatrix = glm::ortho(-1.0f, 0.9f, -0.9f, 1.0f, 2.0f, 9.0f);
	transformMatrix1 = glm::rotate(transformMatrix1, glm::radians(x), glm::vec3(1.0, 0.0, 0.0));
	transformMatrix1 = glm::rotate(transformMatrix1, glm::radians(y), glm::vec3(0.0, 1.0, 0.0));
	drawCube(0.5f, projMatrix * transformMatrix1, shader_programme);
}

void task_4(GLuint shader_programme) {
	glm::mat4 transformMatrix1 = glm::mat4(1.0f);
	transformMatrix1 = glm::translate(transformMatrix1, { 0.0f,0.0f,-4.0f });
	glm::mat4 projMatrix = glm::frustum(-1.0f, 0.9f, -0.9f, 1.0f, 2.0f, 9.0f);
	transformMatrix1 = glm::rotate(transformMatrix1, glm::radians(x), glm::vec3(1.0, 0.0, 0.0));
	transformMatrix1 = glm::rotate(transformMatrix1, glm::radians(y), glm::vec3(0.0, 1.0, 0.0));
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	drawCube(0.5f, projMatrix * transformMatrix1, shader_programme);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}


void task_5(GLuint shader_programme) {
	glm::mat4 transformMatrix1 = glm::mat4(1.0f);
	transformMatrix1 = glm::translate(transformMatrix1, { 0.0f,0.0f,-4.0f });
	glm::mat4 projMatrix = glm::frustum(-1.0f, 0.9f, -0.9f, 1.0f, 2.0f, 9.0f);
	transformMatrix1 = glm::rotate(transformMatrix1, glm::radians(35.0f), glm::vec3(1.0, 0.0, 0.0));
	transformMatrix1 = glm::rotate(transformMatrix1, glm::radians(50.0f), glm::vec3(0.0, 1.0, 0.0));
	drawCube(0.5f, projMatrix * transformMatrix1, shader_programme);
}


void task_6(GLuint shader_programme) {
	glm::mat4 transformMatrix1 = glm::mat4(1.0f);
	transformMatrix1 = glm::translate(transformMatrix1, { 0.0f,0.0f,-4.0f });
	transformMatrix1 = glm::rotate(transformMatrix1, glm::radians(x), glm::vec3(1.0, 0.0, 0.0));
	transformMatrix1 = glm::rotate(transformMatrix1, glm::radians(y), glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 projMatrix = straightOrPerspective==true ? glm::frustum(-1.0f, 0.9f, -0.9f, 1.0f, 2.0f, 9.0f) : glm::ortho(-1.0f, 0.9f, -0.9f, 1.0f, 2.0f, 9.0f);
	drawCube(0.5f, projMatrix * transformMatrix1, shader_programme);


}

void drawCube(GLfloat position, glm::mat4 transformMatrix, GLuint shader_programme) {
			dataPoint dataPoints;
	
			dataPoints.addCoordinates({ position,position,position });
			dataPoints.addCoordinates({ -position,position,position });
			dataPoints.addCoordinates({ position,-position,position });
			dataPoints.addCoordinates({ -position,-position,position });
		
			dataPoints.addCoordinates({ position,position,-position });
			dataPoints.addCoordinates({ -position,position,-position });
			dataPoints.addCoordinates({ position,-position,-position });
			dataPoints.addCoordinates({ -position,-position,-position });
		  
			dataPoints.addCoordinates({ position,position,position });
		  	dataPoints.addCoordinates({-position,position,position});
		  	dataPoints.addCoordinates({position,position,-position});
			dataPoints.addCoordinates({ -position,position,-position});

			dataPoints.addCoordinates({ position,-position,position });
			dataPoints.addCoordinates({ -position,-position,position });
			dataPoints.addCoordinates({ position,-position,-position });
			dataPoints.addCoordinates({ -position,-position,-position });
		 
			dataPoints.addCoordinates({ position,position,position });
			dataPoints.addCoordinates({ position,-position,position });
			dataPoints.addCoordinates({ position,position,-position });
			dataPoints.addCoordinates({ position,-position,-position });

			dataPoints.addCoordinates({ -position,position,position });
			dataPoints.addCoordinates({ -position,-position,position });
			dataPoints.addCoordinates({ -position,position,-position });
			dataPoints.addCoordinates({ -position,-position,-position });

		
	
		 dataPoints.addColors({ 1.0f,0.7f,1.0f});
		 dataPoints.addColors({1.0f,0.7f,1.0f});
		 dataPoints.addColors({1.0f,0.7f,1.0f});
		 dataPoints.addColors({1.0f,0.7f,1.0f});
					
		 dataPoints.addColors({0.6f,1.0f,0.0f});
		 dataPoints.addColors({0.6f,1.0f,0.0f});
		 dataPoints.addColors({0.6f,1.0f,0.0f});
		 dataPoints.addColors({0.6f,1.0f,0.0f});
			
		 dataPoints.addColors({1.0f,0.0f,0.5f});
		 dataPoints.addColors({1.0f,0.0f,0.5f});
		 dataPoints.addColors({1.0f,0.0f,0.5f});
		 dataPoints.addColors({1.0f,0.0f,0.5f});
		
		 dataPoints.addColors({0.0f,0.2f,1.0f});
		 dataPoints.addColors({0.0f,0.2f,1.0f});
		 dataPoints.addColors({0.0f,0.2f,1.0f});
		 dataPoints.addColors({0.0f,0.2f,1.0f});
					
		 dataPoints.addColors({1.0f,1.0f,0.0f});
		 dataPoints.addColors({1.0f,1.0f,0.0f});
		 dataPoints.addColors({1.0f,1.0f,0.0f});
		 dataPoints.addColors({1.0f,1.0f,0.0f});
					 
		 dataPoints.addColors({0.9f,1.0f,1.0f});
		 dataPoints.addColors({0.9f,1.0f,1.0f});
		 dataPoints.addColors({0.9f,1.0f,1.0f});
		 dataPoints.addColors({0.9f,1.0f,1.0f});
		
		std::vector<GLuint> indexes = { 0,1,2,
							  3,1,2,

							  4,5,6,
							  7,5,6,

							  8,9,10,
							  11,9,10,

							  12,13,14,
							  15,13,14,

							  16,17,18,
							  19,17,18,

							  20,21,22,
							  23,21,22,

		};
		drawSmth(dataPoints, indexes, transformMatrix, shader_programme, GL_TRIANGLES);
	}
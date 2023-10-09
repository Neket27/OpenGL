#include "glew.h" // подключение GLEW
#include <glfw3.h> 
#include <iostream> 
#include "ShaderFuncs.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "TimerView.cpp"
#include "dataPoint.h"



int WinWidth = 640;
int WinHeight = 480;

void glfw_window_size_callback(GLFWwindow* window, int width, int height);
void drawSmth(dataPoint dataPoints, std::vector<GLuint> indexes, glm::mat4 transformMatrix, GLuint shader_programme, GLenum type);
void task1(GLuint shader_programme);
void task_1_a(GLint shader_programme);
void task_1_b(GLint shader_programme);
void task_2(GLint shader_programme, bool trueOrFalse);
void task_3(GLint shader_programme);


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

	
	glViewport(0, 0, WinWidth, WinHeight);


	TimerView timerView(shader_programme,window);
	timerView.add(std::chrono::milliseconds(4000), task_1_a);
	timerView.add(std::chrono::milliseconds(4000), task_1_b);
	timerView.add(std::chrono::milliseconds(4000), task_2);
	timerView.add(std::chrono::milliseconds(4000), task_2,true);
	timerView.add(std::chrono::milliseconds(4000), task_3);

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




void task_1_a(GLint shader_programme) {
	std::vector<GLuint> indexes = { 
					   0,1,2,
					   0,1,3,
					   0,1,4,
					   0,2,3,
					   0,2,4,
					   0,3,4,
					   1,2,3,
					   1,2,4,
					   1,3,4,
					   2,3,4,

	};

	dataPoint dataPoints;
	dataPoints.addCoordinates({ 0.0f, 0.5f, 0.0f });
	dataPoints.addCoordinates({ 0.5f, 0.0f, 0.0f });
	dataPoints.addCoordinates({ 0.0f, -0.5f, 1.0f });
	dataPoints.addCoordinates({ -0.5f, 0.0f, 0.0f });
	dataPoints.addCoordinates({ -1.0f, 0.0f, 0.0f });

	dataPoints.addColors({ 1.0f, 0.0f, 0.0f });
	dataPoints.addColors({ 0.0f, 1.0f, 0.0f });
	dataPoints.addColors({ 0.0f, 0.0f, 1.0f });
	dataPoints.addColors({ 1.0f, 1.0f, 0.0f });
	dataPoints.addColors({ 1.0f, 1.0f, 1.0f });

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // отрисовка только граний
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	drawSmth(dataPoints, indexes, transformMatrix, shader_programme, GL_TRIANGLES);
}


void task_1_b(GLint shader_programme) {
	std::vector<GLuint> indexes = {
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

	dataPoint dataPoints;
	dataPoints.addCoordinates({ 0.0f, 0.5f, 0.0f });
	dataPoints.addCoordinates({ 0.5f, 0.0f, 0.0f });
	dataPoints.addCoordinates({ 0.0f, -0.5f, 1.0f });
	dataPoints.addCoordinates({ -0.5f, 0.0f, 0.0f });
	dataPoints.addCoordinates({ -1.0f, 0.0f, 0.0f });
	dataPoints.addCoordinates({ 0.0f, 1.0f, 0.0f });

	dataPoints.addColors({ 1.0f, 0.0f, 0.0f });
	dataPoints.addColors({ 0.0f, 1.0f, 0.0f });
	dataPoints.addColors({ 0.0f, 0.0f, 1.0f });
	dataPoints.addColors({ 1.0f, 1.0f, 0.0f });
	dataPoints.addColors({ 1.0f, 1.0f, 1.0f });
	dataPoints.addColors({ 0.4f, 1.0f, 0.7f });

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // отрисовка только граний
	glm::mat4 transformMatrix = glm::mat4(1.0f);
	drawSmth(dataPoints, indexes, transformMatrix, shader_programme, GL_LINES);
}


void task_2(GLint shader_programme, bool trueOrFalse) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	dataPoint dataPoints;
	dataPoints.addCoordinates({ -0.4f,0.2f,0.0f });
	dataPoints.addCoordinates({ -0.6f,-0.3f,0.0f });
	dataPoints.addCoordinates({ -0.2f,-0.3f,0.0f });
	dataPoints.addColors({ 1.0f,0.0f,0.0f });
	dataPoints.addColors({ 0.0f,1.0f,0.0f });
	dataPoints.addColors({ 0.0f,0.0f,1.0f });
	std::vector<GLuint> indexes1 = { 0,1,2 };


	glm::mat4 transformMatrix = glm::mat4(1.0f);
	glm::vec3 vector_P = { 0.03f,0.15f,0.0f };
	glm::vec3 scale = { 1.2f,1.5f,0.0f };
	
	if (trueOrFalse) {
	//зд:	треугольник следует смасштабировать с коэффициентами(kx, ky) и перенести на вектор p;
		transformMatrix = glm::translate(transformMatrix, vector_P); // перенос на вектор p
		transformMatrix = glm::scale(transformMatrix, scale); // маштабирование
	}
	drawSmth(dataPoints, indexes1, transformMatrix, shader_programme, GL_TRIANGLES);

	dataPoint dataPoints2;
	dataPoints2.addCoordinates({ 0.0f,0.5f,0.0f });
	dataPoints2.addCoordinates({ 0.0f,-0.5f,0.0f });
	dataPoints2.addColors({ 1.0f,0.0f,0.0f });
	dataPoints2.addColors({ 0.0f,1.0f,0.0f });
	std::vector<GLuint> indexes2 = { 0,1 };

	transformMatrix = glm::mat4(1.0f);
	if (trueOrFalse) transformMatrix = glm::rotate(transformMatrix, glm::radians(40.0f), glm::vec3(0.0, 0.0, 1.0)); //поворачивает 3D вектор на заданный угол вокруг заданной оси(представленной орт - вектором) :
	drawSmth(dataPoints2,indexes2, transformMatrix, shader_programme, GL_LINES);


	dataPoint dataPoints3;

	dataPoints3.addCoordinates({ 0.4f,0.5f,0.0f });
	dataPoints3.addCoordinates({ 0.7f,0.5f,0.0f });
	dataPoints3.addCoordinates({ 0.4f,-0.5f,0.0f });
	dataPoints3.addCoordinates({ 0.7f,-0.5f,0.0f });
	dataPoints3.addColors({ 0.1f,0.1f,0.9f });
	dataPoints3.addColors({ 0.7f,0.1f,0.0f });
	dataPoints3.addColors({ 0.7f,0.1f,0.0f });
	dataPoints3.addColors({ 0.1f,0.1f,0.9f });
	std::vector<GLuint> indexes3 = { 0,1,2,2,1,3 };
	
	transformMatrix = glm::mat4(1.0f);
	if (trueOrFalse) transformMatrix = glm::rotate(transformMatrix, glm::radians(-25.0f), glm::vec3(-0.3, -0.8, 1.0)); //поворачивает 3D вектор на заданный угол вокруг заданной оси(представленной орт - вектором) :
	drawSmth(dataPoints3, indexes3, transformMatrix, shader_programme, GL_TRIANGLES);

}


void task_3(GLint shader_programme) {
	dataPoint dataPoints;
	dataPoints.addCoordinates({ 0.0f,0.0f,0.0f });
	dataPoints.addCoordinates({ 0.0f,0.5f,0.0f });
	dataPoints.addColors({ 1.0f,0.0f,0.0f });
	dataPoints.addColors({ 0.0f,1.0f,0.0f });
	std::vector<GLuint> indexes = { 0,1 };

	glm::mat4 transformMatrix = glm::mat4(1.0f);
	drawSmth(dataPoints, indexes, transformMatrix, shader_programme, GL_LINES);
	transformMatrix = glm::rotate(transformMatrix, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0)); //поворачивает 3D вектор на заданный угол вокруг заданной оси(представленной орт - вектором) :
	drawSmth(dataPoints, indexes, transformMatrix, shader_programme, GL_LINES);
	transformMatrix = glm::rotate(transformMatrix, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0)); //поворачивает 3D вектор на заданный угол вокруг заданной оси(представленной орт - вектором) :
	drawSmth(dataPoints, indexes, transformMatrix, shader_programme, GL_LINES);
	transformMatrix = glm::rotate(transformMatrix, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0)); //поворачивает 3D вектор на заданный угол вокруг заданной оси(представленной орт - вектором) :
	drawSmth(dataPoints, indexes, transformMatrix, shader_programme, GL_LINES);
	transformMatrix = glm::rotate(transformMatrix, glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0)); //поворачивает 3D вектор на заданный угол вокруг заданной оси(представленной орт - вектором) :
	drawSmth(dataPoints, indexes, transformMatrix, shader_programme, GL_LINES);
	transformMatrix = glm::rotate(transformMatrix, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0)); //поворачивает 3D вектор на заданный угол вокруг заданной оси(представленной орт - вектором) :
	drawSmth(dataPoints, indexes, transformMatrix, shader_programme, GL_LINES);


}
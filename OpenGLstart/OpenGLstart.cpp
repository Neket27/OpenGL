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

void glfw_window_size_callback(GLFWwindow* window, int width, int height);
void drawSmth(dataPoint dataPoints, std::vector<GLuint> indexes, glm::mat4 transformMatrix, GLuint shader_programme, GLenum type);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void task_1And2(GLint shader_programme);
void task_1_b(GLint shader_programme);
void task_2(GLint shader_programme, bool trueOrFalse);
void task_3(GLuint shader_programme);
void task_4(GLuint shader_programme);
void task_5(GLuint shader_programme);
void drawSmth2(glm::vec3 colors[], glm::vec3 points[], GLuint indexes[], glm::mat4 transformMatrix, GLuint shader_programme, GLenum type, int n, int ind);
void drawCube2(GLint shader_programme);
void drawCube(GLfloat size, glm::mat4 transformMatrix1, GLuint shader_programme);

void genSphere(
	std::vector<GLuint>& outIndexes, //Выходной массив индексов
	std::vector < glm::vec3 >& outVertices, //Выходной массив координат
	std::vector < glm::vec2 >& outTextures, //Выходной массив текстурных координат
	std::vector < glm::vec3 >& outNormals, //Выходной массив векторов нормалей
	float radius, //Радиус сферы
	int sectorCount, //Число меридианов
	int stackCount //Число параллелей
);

int  numberTask = 0;
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
		
	}


		glfwSwapBuffers(window);
	}


	//TimerView timerView(shader_programme, window);
	//timerView.add(std::chrono::milliseconds(40000), task_1_a);
	//timerView.add(std::chrono::milliseconds(4000), task_1_b);
	//timerView.add(std::chrono::milliseconds(4000), task_2);
	//timerView.add(std::chrono::milliseconds(4000), task_2, true);
	//timerView.add(std::chrono::milliseconds(4000), task_3);

	glfwTerminate();
	return 0;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	else  if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		numberTask = (numberTask++) % 5;
	else  if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
		x -= 1;
	else  if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
		x += 1;
	else  if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
		y -= 1;
	else  if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
		y += 1;
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
	drawSmth(dataPoints2, indexes2, transformMatrix, shader_programme, GL_LINES);


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


void task_3(GLuint shader_programme) {
	glm::mat4 transformMatrix1 = glm::mat4(1.0f);
	transformMatrix1 = glm::translate(transformMatrix1, { 0.0f,0.0f,-4.0f });
	//glm::mat4 projMatrix = glm::ortho(-1.0f, 0.9f, -0.9f, 1.0f, 2.0f, 9.0f);
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



void genSphere(
	std::vector<GLuint>& outIndexes, //Выходной массив индексов
	std::vector < glm::vec3 >& outVertices, //Выходной массив координат
	std::vector < glm::vec2 >& outTextures, //Выходной массив текстурных координат
	std::vector < glm::vec3 >& outNormals, //Выходной массив векторов нормалей
	float radius, //Радиус сферы
	int sectorCount, //Число меридианов
	int stackCount //Число параллелей
)
{
	//Очистка выходных массивов
	outIndexes.clear();
	outNormals.clear();
	outVertices.clear();
	outTextures.clear();
	//Вспомогательные переменные для хранения промежуточных данных
		float x, y, z, xy;
		float PI = 3.14;
	float nx, ny, nz, lengthInv = 1.0f / radius;
	float s, t;
	float sectorStep = 2.0f * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;
	//Цикл по каждой параллели
	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep; // начиная от PI/2 и до -PI/2
		xy = radius * cosf(stackAngle); // r * cos(u)
		z = radius * sinf(stackAngle); // r * sin(u)
		// На каждую параллель добавляется (sectorCount+1) вершин
		// для первой и последней совпадают позиция и нормаль, но отличаются текстурные координаты
			for (int j = 0; j <= sectorCount; ++j)
			{
				sectorAngle = j * sectorStep; // от 0 до 2PI
				// высчитываются координаты (x, y, z)
				x = xy * cosf(sectorAngle); // r * cos(u) * cos(v)
				y = xy * sinf(sectorAngle); // r * cos(u) * sin(v)
				glm::vec3 vert;
				vert.x = x;
				vert.y = y;
				vert.z = z;
				outVertices.push_back(vert);
				
					// высчитывается вектор нормали (nx, ny, nz)
					nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;
				glm::vec3 norm;
				norm.x = nx;
				norm.y = ny;
				norm.z = nz;
				outNormals.push_back(norm);
				// высчитываются текстурные координаты (s, t) в диапазоне [0, 1]
				s = (float)j / sectorCount;
				t = (float)i / stackCount;
				glm::vec2 vt;
				vt.s = s;
				vt.t = t;
				outTextures.push_back(vt);
			}
		//Но координат мало - нужен порядок обхода, т.е. индексы
		int k1, k2;
		for (int i = 0; i < stackCount; ++i)
		{
			k1 = i * (sectorCount + 1); // начало текущего меридиана
			k2 = k1 + sectorCount + 1; // начало следующего меридиана
			for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
			{
				// Для первой и последней параллели по 1 треугольнику, для остальных - по два
					// k1 => k2 => k1+1
					if (i != 0)
					{
						outIndexes.push_back(k1);
						outIndexes.push_back(k2);
						outIndexes.push_back(k1 + 1);
					
					}
				// k1+1 => k2 => k2+1
				if (i != (stackCount - 1))
				{
					outIndexes.push_back(k1 + 1);
					outIndexes.push_back(k2);
					outIndexes.push_back(k2 + 1);
				}
			}
		}
	}
}


void drawCube2(GLint shader_programme) {
	
	glm::vec3 g_vertex_buffer_data[] = {
		{-1.0f,-1.0f,-1.0f}, // triangle 1 : begin
		{-1.0f,-1.0f, 1.0f},
		{-1.0f, 1.0f, 1.0f}, // triangle 1 : end
		{1.0f, 1.0f,-1.0f,}, // triangle 2 : begin
		{-1.0f,-1.0f,-1.0f},
		{-1.0f, 1.0f,-1.0f}, // triangle 2 : end
		{1.0f,-1.0f, 1.0f,},
		{-1.0f,-1.0f,-1.0f},
		{1.0f,-1.0f,-1.0f,},
		{1.0f, 1.0f,-1.0f,},
		{1.0f,-1.0f,-1.0f,},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f, 1.0f, 1.0f},
		{-1.0f, 1.0f,-1.0f},
		{1.0f,-1.0f, 1.0f,},
		{-1.0f,-1.0f, 1.0f},
		{-1.0f,-1.0f,-1.0f},
		{-1.0f, 1.0f, 1.0f},
		{-1.0f,-1.0f, 1.0f},
		{1.0f,-1.0f, 1.0f,},
		{1.0f, 1.0f, 1.0f,},
		{1.0f,-1.0f,-1.0f,},
		{1.0f, 1.0f,-1.0f,},
		{1.0f,-1.0f,-1.0f,},
		{1.0f, 1.0f, 1.0f,},
		{1.0f,-1.0f, 1.0f,},
		{1.0f, 1.0f, 1.0f,},
		{1.0f, 1.0f,-1.0f,},
		{-1.0f, 1.0f,-1.0f},
		{1.0f, 1.0f, 1.0f,},
		{-1.0f, 1.0f,-1.0f},
		{-1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f,},
		{-1.0f, 1.0f, 1.0f},
		{1.0f,-1.0f, 1.0f }
	};

	// One color for each vertex. They were generated randomly.
	glm::vec3 colors[] = {
		{0.583f,  0.771f,  0.014f},
		{0.609f,  0.115f,  0.436f},
		{0.327f,  0.483f,  0.844f},
		{0.822f,  0.569f,  0.201f},
		{0.435f,  0.602f,  0.223f},
		{0.310f,  0.747f,  0.185f},
		{0.597f,  0.770f,  0.761f},
		{0.559f,  0.436f,  0.730f},
		{0.359f,  0.583f,  0.152f},
		{0.483f,  0.596f,  0.789f},
		{0.559f,  0.861f,  0.639f},
		{0.195f,  0.548f,  0.859f},
		{0.014f,  0.184f,  0.576f},
		{0.771f,  0.328f,  0.970f},
		{0.406f,  0.615f,  0.116f},
		{0.676f,  0.977f,  0.133f},
		{0.971f,  0.572f,  0.833f},
		{0.140f,  0.616f,  0.489f},
		{0.997f,  0.513f,  0.064f},
		{0.945f,  0.719f,  0.592f},
		{0.543f,  0.021f,  0.978f},
		{0.279f,  0.317f,  0.505f},
		{0.167f,  0.620f,  0.077f},
		{0.347f,  0.857f,  0.137f},
		{0.055f,  0.953f,  0.042f},
		{0.714f,  0.505f,  0.345f},
		{0.783f,  0.290f,  0.734f},
		{0.722f,  0.645f,  0.174f},
		{0.302f,  0.455f,  0.848f},
		{0.225f,  0.587f,  0.040f},
		{0.517f,  0.713f,  0.338f},
		{0.053f,  0.959f,  0.120f},
		{0.393f,  0.621f,  0.362f},
		{0.673f,  0.211f,  0.457f},
		{0.820f,  0.883f,  0.371f},
		{0.982f,  0.099f,  0.879f}
	};
	GLuint indexes1[] = {    0,1,2,
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


	glm::mat4 transformMatrix = glm::mat4(1.0f);
	drawSmth2(colors, g_vertex_buffer_data, indexes1, transformMatrix, shader_programme, GL_TRIANGLES, 24, 36);



	};

	void drawSmth2(glm::vec3 colors[], glm::vec3 points[], GLuint indexes[], glm::mat4 transformMatrix, GLuint shader_programme, GLenum type, int n, int ind) {
		GLuint stm = glGetUniformLocation(shader_programme, "transform");
		glUniformMatrix4fv(stm, 1, GL_FALSE, &transformMatrix[0][0]);
		GLuint coords_vbo = 0;
		glGenBuffers(1, &coords_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
		glBufferData(GL_ARRAY_BUFFER, n * 3 * sizeof(GLfloat), points, GL_STATIC_DRAW);
		GLuint colors_vbo = 0;
		glGenBuffers(1, &colors_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, n * 3 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
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



	void drawCube(GLfloat size, glm::mat4 transformMatrix1, GLuint shader_programme) {
		glm::vec3 points1[] = {
		  {size,size,size},
		  {-size,size,size},
		  {size,-size,size},
		  {-size,-size,size},

		  {size,size,-size},
		  {-size,size,-size},
		  {size,-size,-size},
		  {-size,-size,-size},

		  {size,size,size},
		  {-size,size,size},
		  {size,size,-size},
		  {-size,size,-size},

		  {size,-size,size},
		  {-size,-size,size},
		  {size,-size,-size},
		  {-size,-size,-size},

		  {size,size,size},
		  {size,-size,size},
		  {size,size,-size},
		  {size,-size,-size},

		  {-size,size,size},
		  {-size,-size,size},
		  {-size,size,-size},
		  {-size,-size,-size},

		};
		glm::vec3 colors1[] = {
		 {1.0f,0.7f,1.0f},
		 {1.0f,0.7f,1.0f},
		 {1.0f,0.7f,1.0f},
		 {1.0f,0.7f,1.0f},

		 {0.6f,1.0f,0.0f},
		 {0.6f,1.0f,0.0f},
		 {0.6f,1.0f,0.0f},
		 {0.6f,1.0f,0.0f},

		 {1.0f,0.0f,0.5f},
		 {1.0f,0.0f,0.5f},
		 {1.0f,0.0f,0.5f},
		 {1.0f,0.0f,0.5f},

		 {0.0f,0.2f,1.0f},
		 {0.0f,0.2f,1.0f},
		 {0.0f,0.2f,1.0f},
		 {0.0f,0.2f,1.0f},

	

		 {1.0f,1.0f,0.0f},
		 {1.0f,1.0f,0.0f},
		 {1.0f,1.0f,0.0f},
		 {1.0f,1.0f,0.0f},

		 {0.9f,1.0f,1.0f},
		 {0.9f,1.0f,1.0f},
		 {0.9f,1.0f,1.0f},
		 {0.9f,1.0f,1.0f},
		};
		GLuint indexes1[] = { 0,1,2,
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
		drawSmth2(colors1, points1, indexes1, transformMatrix1, shader_programme, GL_TRIANGLES, 24, 36);
	}
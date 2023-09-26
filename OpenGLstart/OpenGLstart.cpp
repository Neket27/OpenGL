#include <windows.h>
#include <iostream>
#include <vector>

using namespace std;

#include "glew.h" // подключение GLEW
#include <GLFW/glfw3.h> // подключение GLFW
#include <stdio.h> //Для простого консольного вывода ошибок

#pragma comment( lib, "OpenGL32.lib" )

int main() {
	//Для начала инициализация всего
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}
	// Для MacOs надо добавить вот это всё
	//По сути это необходимо для выбора новейшей версии OpenGL вместо стандартной 3.2
		/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
	   GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE,
	   GLFW_OPENGL_CORE_PROFILE);*/

	   //Создание окна. OpenGL в такое не может - тут и помогает GLFW
	   //Параметры - размеры окна, заголовок, указатели на монитор и родительское окно
	GLFWwindow* window = glfwCreateWindow(640, 480, "Triangle",
		NULL, NULL);

	//Если не вышло - ругаемся
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;

	}
	//Созданное окно выбирается как текущее
	glfwMakeContextCurrent(window);
	// Подключение новейшей из доступных версий OpenGL
	glewExperimental = GL_TRUE;
	//Включение GLEW
	glewInit();
	// Получение версии OpenGL просто чтобы убедиться что оно работает
	const GLubyte* renderer = glGetString(GL_RENDERER); // информация о графической карте
	const GLubyte* version = glGetString(GL_VERSION); // информация о версии OpenGL
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	// Включение буфера глубины и определение его работы
	glEnable(GL_DEPTH_TEST); // Включение буфера глубины
	glDepthFunc(GL_LESS); // А вот тут можно управлять его работой. Сейчас установлен режим по умолчанию
	// А теперь просто рисование
	//Рисовать будем треугольник
	//Для начала определение координат

	//А теперь идёт магия

	\



	struct shape {
		std::vector<GLfloat>  vertices; //Here we use a vector (similar to C# lists) instead of an arry to store our vertices as it is more flexible.
		GLuint VAO;
		GLuint VBO;
		std::vector<GLfloat> COLOR;
	};
	shape triangle1;
	shape triangle2;
	shape triangle3;

	triangle1.vertices = {
		 0.0f, 0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f };

	triangle2.vertices = {
		-0.3f, -0.8f, 0.0f,
		-0.3f, -0.5f, 0.0f,
		-0.2f, -0.5f, 0.3f };

	triangle3.vertices = {
		0.4f, 0.3f, 0.0f,
		0.95f, -0.3f, 0.0f,
		0.95f, 0.3f, 0.0f };

	triangle1.COLOR = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f };

	triangle2.COLOR = {
		0.0f, 1.0f, 1.0f,
		0.7f, 0.2f, 1.0f,
		1.0f, 0.0f, 0.4f };
		
	triangle3.COLOR = {
		1.0f, 0.3f, 1.0f,
		0.7f, 0.7f, 0.7f,
		0.5f, 0.5f, 0.4f };

	GLfloat points[] = {
0.0f, 0.5f, 0.0f,
0.5f, -0.5f, 0.0f,
-0.5f, -0.5f, 0.0f
	};

	GLfloat colors[] = {
1.0f, 0.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 0.0f, 1.0f
	};




	//Теперь сложная часть
	//Основа современной трёхмерной графики - шейдеры
	//Собственно даже для базового вывода необходимо описать хотя бы два -
		//вершинный и фрагментный
		//Вершинный шейдер отвечает за отображение точек на экране
		//В частности он обеспечивает проецирование
		//Минимальный шейдер состоит из следующих элементов:
	const char* vertex_shader =
		//Версия шейдера 400 для OpenGL 4, 150 для 3.2, 330 для 3.3 
		"#version 400\n"
		"in vec3 vertex_position;"
		"in vec3 vertex_colour;"
		"out vec3 colour;"

	"void main() {"
		"colour = vertex_colour;"
		"gl_Position = vec4(vertex_position, 1.0);"
		"}";

	//Фрагментный шейдер отвечает за окрашивание каждого фрагмента
	//Фрагмент - это по сути один пиксель на экране
	const char* fragment_shader =
		"#version 400\n"
		"in vec3 colour;"
		"out vec4 frag_colour;"

		"void main() {"
		//В функции статично задаётся цвет для каждого фрагмента
		//Пусть будет что-то бирюзовое
		//Для ускорения цвет не высчитывается, а константный
		//" frag_colour = vec4(0.19, 0.84, 0.78, 1.0);"
		//" frag_colour = vec4(0.9, 0.24, 0.65, 0.47);"
		"frag_colour = vec4(colour, 1.0);"
		"}";



	GLuint coords_vbo = 0;
	GLuint colors_vbo = 0;
	

	glGenBuffers(1, &coords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &triangle1.vertices.at(0),GL_STATIC_DRAW);
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &triangle1.vertices.at(0),GL_STATIC_DRAW);

	glGenVertexArrays(1, &triangle1.VAO);
	glBindVertexArray(triangle1.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);




	
	glGenBuffers(1, &coords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &triangle2.vertices.at(0), GL_STATIC_DRAW);
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &triangle2.COLOR.at(0), GL_STATIC_DRAW);

	glGenVertexArrays(1, &triangle2.VAO);
	glBindVertexArray(triangle2.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);



	glGenBuffers(1, &coords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &triangle3.vertices.at(0), GL_STATIC_DRAW);
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), &triangle3.COLOR.at(0), GL_STATIC_DRAW);

	glGenVertexArrays(1, &triangle3.VAO);
	glBindVertexArray(triangle3.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//Теперь надо загрузить программы шейдеров и скомпилировать их
    //Создаётся шейдер
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	//Загружается его программа
	glShaderSource(vs, 1, &vertex_shader, NULL);
	//Компилируется
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	//Создаётся программа
		GLuint shader_programme = glCreateProgram();
	glAttachShader(shader_programme, vs);
	glAttachShader(shader_programme, fs);
	glBindAttribLocation(shader_programme, 0, "vertex_position");
	glBindAttribLocation(shader_programme, 1, "vertex_colour");
	glLinkProgram(shader_programme);

	//Программа компонуется
	glLinkProgram(shader_programme);




	while (!glfwWindowShouldClose(window)) {
		// Закрашивается фон окна
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// Подключается шейдерная программа
		glUseProgram(shader_programme);
		// Подключается массив вершин
		glBindVertexArray(triangle1.VAO);
		// Из массива рисуются три элемента начиная с элемента с индексом 0
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(triangle2.VAO);
		// Из массива рисуются три элемента начиная с элемента с индексом 0
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(triangle3.VAO);
		// Массив рисуется, при этом используется объединение вершин в треугольники
			// Из массива рисуются три элемента начиная с элемента с индексом 0
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	
		



		// Обработка очереди событий
		glfwPollEvents();
		// Использование двойной буферизации
		glfwSwapBuffers(window);
	}
	// Завершение работы и удаление окон
	glfwTerminate();
	return 0;
}

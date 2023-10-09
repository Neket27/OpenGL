#include "glew.h" // подключение GLEW
#include <glfw3.h> 
#include <chrono>
#include <vector>
#include <functional>
#include <thread>

class TimerView {
public:

	TimerView(GLuint shader_programme, GLFWwindow* window) : shader_programme(shader_programme), window(window) {}

	void add(std::chrono::milliseconds delay_ms, std::function<void(GLuint shader_programme)> callback) {
		// Создаем объект std::chrono::milliseconds для задержки
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_programme);

		callback(shader_programme); // Здесь передаем shader_programme в callback
		glfwSwapBuffers(window);
		std::chrono::milliseconds delay(delay_ms);
		std::this_thread::sleep_for(delay);

	}


	void add(std::chrono::milliseconds delay_ms, std::function<void(GLuint shader_programme, bool trueOrFalse)> callback, bool trueOrFalseFlag = false) {
		// Создаем объект std::chrono::milliseconds для задержки
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shader_programme);

		callback(shader_programme, trueOrFalseFlag); // Здесь передаем shader_programme в callback
		glfwSwapBuffers(window);
		std::chrono::milliseconds delay(delay_ms);
		std::this_thread::sleep_for(delay);

	}

private:
	GLuint shader_programme; // Добавьте поле для хранения shader_programme
	GLFWwindow* window;
};


#include "glew.h"
#include <glfw3.h> 
#include <iostream> 
#include "ShaderFuncs.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "dataPoint.h"

#include "Object.h"
#include <cmath>
int WinWidth = 1240;
int WinHeight = 780;

void glfw_window_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


int chse;
GLfloat dist;
GLfloat ang;
GLfloat mv;
GLfloat rt;

int main() {
    dist = 35.0f;
    ang = 0.0f;
    mv = 0.0f;
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WinWidth, WinHeight, "PR5",
        NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetWindowSizeCallback(window, glfw_window_size_callback);
    glfwSetKeyCallback(window, key_callback);
    GLuint vs = LoadShader("VertexShader.glsl", GL_VERTEX_SHADER);
    GLuint fs = LoadShader("FragmentShader.glsl", GL_FRAGMENT_SHADER);
    GLuint shader_programme = glCreateProgram();
    glAttachShader(shader_programme, vs);
    glAttachShader(shader_programme, fs);
    glBindAttribLocation(shader_programme, 0, "vertex_position");
    glBindAttribLocation(shader_programme, 1, "vertex_colour");
    glLinkProgram(shader_programme);
    chse = 0;
    OpenGLENG::Object* pl = OpenGLENG::Object::LoadFromOBJ("v.obj", { 0.2f,0.7f,0.8f });
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glViewport(0, 0, WinWidth, WinHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shader_programme);
        glm::mat4 trm = glm::mat4(1.0f);
        trm = glm::translate(trm, { 0.0f,-5.0f,mv });
        trm = glm::rotate(trm, glm::radians(0.0f), glm::vec3(1.0, 1.0, 0.0));
        trm = glm::rotate(trm, rt, glm::vec3(0.0, 0.0, 1.0));
        glm::vec3 scale = { 0.2f,0.2f,0.2f };
        trm = glm::scale(trm, scale); // уменьшение
        glm::mat4 prsp = glm::perspective(glm::radians(35.0f), (float)WinWidth / WinHeight, 0.0f, 70.0f);
        glm::mat4 cam = glm::lookAt(glm::vec3(dist * cos(ang), 0.5f, dist * sin(ang)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.1f, 0.0f));
        pl->draw(prsp * cam * trm, shader_programme);
        glfwSwapBuffers(window);
    }
    glDeleteShader(vs);
    glDeleteShader(fs);
    glDeleteShader(shader_programme);
    delete pl;
    glfwTerminate();
    return 0;
}

void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
    WinWidth = width;
    WinHeight = height;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    else  if (key == GLFW_KEY_DOWN && action == GLFW_REPEAT)
        dist += 0.05f;
    else  if (key == GLFW_KEY_UP && action == GLFW_REPEAT)
        dist -= 0.05f;
    else  if (key == GLFW_KEY_LEFT && action == GLFW_REPEAT)
        ang -= 0.01f;
    else  if (key == GLFW_KEY_RIGHT && action == GLFW_REPEAT)
        ang += 0.01f;
    else  if (key == GLFW_KEY_A && action == GLFW_REPEAT)
        mv += 0.01f;
    else  if (key == GLFW_KEY_D && action == GLFW_REPEAT)
        mv -= 0.01f;
    else  if (key == GLFW_KEY_W && action == GLFW_REPEAT)
        rt += 0.01f;
    else  if (key == GLFW_KEY_S && action == GLFW_REPEAT)
        rt -= 0.01f;

}
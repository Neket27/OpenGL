#include "glew.h" // подключение GLEW
#include <GLFW/glfw3.h> 
#include <iostream> 
#include "ShaderFuncs.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
int WinWidth = 640;
int WinHeight = 480;

void drawSmth(glm::vec3 colors[], glm::vec3 points[], GLuint indexes[],
    glm::mat4 transformMatrix, GLuint shader_programme, GLenum type, int n, int
    ind);
void glfw_window_size_callback(GLFWwindow* window, int width, int height);
void task1(GLuint shader_programme);
void task2(GLuint shader_programme, bool on);
void task3(GLuint shader_programme);

int dev() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WinWidth, WinHeight, "PR3",
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
    int task = 0;
    bool on = false;
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, 1);
        }
        else if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ENTER)) {
            on = true;
        }
        else if ((GLFW_RELEASE == glfwGetKey(window, GLFW_KEY_ENTER)) && on) {
            task = (++task) % 4;
            on = false;
        }
        glViewport(0, 0, WinWidth, WinHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_programme);
        switch (task) {
        case 0:
            task1(shader_programme);
            break;
        case 1:
            task2(shader_programme, false);
            break;
        case 2:
            task2(shader_programme, true);
            break;
        case 3:
            task3(shader_programme);
            break;
        }
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}

void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
    WinWidth = width;
    WinHeight = height;
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
    drawSmth(colors, points, indexes, transformMatrix, shader_programme,
        GL_TRIANGLES, 6, 36);
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
    drawSmth(colors2, points2, indexes2, transformMatrix, shader_programme,
        GL_LINES, 6, 30);
}
void task2(GLuint shader_programme, bool trf) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glm::vec3 points1[] = {
           {-0.7f,0.3f,0.0f},
           {-1.0f,-0.3f,0.0f},
           {-0.4f,-0.3f,0.0f}
    };
    glm::vec3 colors1[] = {
      {1.0f,0.0f,0.0f},
      {0.0f,1.0f,0.0f},
      { 0.0f,0.0f,1.0f}
    };
    GLuint indexes1[] = { 0,1,2 };
    glm::mat4 transformMatrix = glm::mat4(1.0f);
    glm::vec3 position = { 0.1f,-0.05f,0.0f };
    glm::vec3 scale = { -0.5f,1.5f,0.0f };
    if (trf) {
        transformMatrix = glm::translate(transformMatrix, position);
        transformMatrix = glm::scale(transformMatrix, scale);
    }
    drawSmth(colors1, points1, indexes1, transformMatrix, shader_programme,
        GL_TRIANGLES, 3, 3);
    glm::vec3 points2[] = {
           {0.0f,0.5f,0.0f},
           {0.0f,-0.5f,0.0f},
    };
    glm::vec3 colors2[] = {
      {1.0f,0.0f,0.0f},
      {0.0f,1.0f,0.0f},
    };
    GLuint indexes2[] = { 0,1 };
    transformMatrix = glm::mat4(1.0f);
    if (trf) transformMatrix = glm::rotate(transformMatrix,
        glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
    drawSmth(colors2, points2, indexes2, transformMatrix, shader_programme,
        GL_LINES, 2, 2);
    glm::vec3 points3[] = {
           {0.4f,0.5f,0.0f},
           {0.7f,0.5f,0.0f},
           {0.4f,-0.5f,0.0f},
           {0.7f,-0.5f,0.0f},
    };
    glm::vec3 colors3[] = {
      {1.0f,0.0f,0.0f},
      {1.0f,0.0f,0.0f},
      {1.0f,0.0f,0.0f},
      {1.0f,0.0f,0.0f},
    };
    GLuint indexes3[] = { 0,1,2,2,1,3 };
    transformMatrix = glm::mat4(1.0f);
    if (trf) transformMatrix = glm::rotate(transformMatrix, glm::radians(-
        30.0f), glm::vec3(-0.1, 0.3, 1.0));
    drawSmth(colors3, points3, indexes3, transformMatrix, shader_programme,
        GL_TRIANGLES, 4, 6);
}
void task3(GLuint shader_programme) {
    glm::vec3 points2[] = {
          {0.0f,0.0f,0.0f},
          {-0.5f,0.0f,0.0f},
          {-0.5f,0.3f,0.0f},
    };
    glm::vec3 colors2[] = {
      {1.0f,0.0f,0.0f},
      {0.0f,1.0f,1.0f},
      {0.0f,0.0f,1.0f},
    };
    GLuint indexes2[] = { 0,1,1,2,2,0 };
    glm::mat4 transformMatrix = glm::mat4(1.0f);
    drawSmth(colors2, points2, indexes2, transformMatrix, shader_programme,
        GL_LINES, 3, 6);
    transformMatrix = glm::rotate(transformMatrix, glm::radians(180.0f),
        glm::vec3(0.0, 1.0, 0.0));
    drawSmth(colors2, points2, indexes2, transformMatrix, shader_programme,
        GL_LINES, 3, 6);
    transformMatrix = glm::mat4(1.0f);
    transformMatrix = glm::rotate(transformMatrix, glm::radians(-225.0f),
        glm::vec3(0.0, 0.0, 1.0));
    glm::vec3 scale = { 0.75f,0.75f,0.0f };
    transformMatrix = glm::scale(transformMatrix, scale);
    drawSmth(colors2, points2, indexes2, transformMatrix, shader_programme,
        GL_LINES, 3, 6);
    transformMatrix = glm::mat4(1.0f);
    transformMatrix = glm::rotate(transformMatrix, glm::radians(180.0f),
        glm::vec3(0.0, 1.0, 0.0));
    transformMatrix = glm::rotate(transformMatrix, glm::radians(-225.0f),
        glm::vec3(0.0, 0.0, 1.0));
    scale = { 0.75f,0.75f,0.0f };
    transformMatrix = glm::scale(transformMatrix, scale);
    drawSmth(colors2, points2, indexes2, transformMatrix, shader_programme,
        GL_LINES, 3, 6);
}
void drawSmth(glm::vec3 colors[], glm::vec3 points[], GLuint indexes[],
    glm::mat4 transformMatrix, GLuint shader_programme, GLenum type, int n, int
    ind) {
    GLuint stm = glGetUniformLocation(shader_programme, "transform");
    glUniformMatrix4fv(stm, 1, GL_FALSE, &transformMatrix[0][0]);
    GLuint coords_vbo = 0;
    glGenBuffers(1, &coords_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
    glBufferData(GL_ARRAY_BUFFER, n * 3 * sizeof(GLfloat), points,
        GL_STATIC_DRAW);
    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, n * 3 * sizeof(GLfloat),
        colors, GL_STATIC_DRAW);
    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind * sizeof(GLuint), indexes,
        GL_STATIC_DRAW);
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

#include "glew.h" // подключение GLEW
#include <GLFW/glfw3.h> 
#include <iostream> 
#include "ShaderFuncs.h"
int WinWidth = 640;
int WinHeight = 480;

void drawSmth(GLfloat* colors, GLfloat* points, GLfloat startx, GLfloat starty, GLfloat size, GLenum type, int n);
void glfw_window_size_callback(GLFWwindow* window, int width, int height);
void drawHexagonDots(GLfloat startx, GLfloat starty, GLfloat size);
void drawHexagon(GLfloat startx, GLfloat starty, GLfloat size);
void drawLineStrip(GLfloat startx, GLfloat starty, GLfloat size);
void drawLineLoop(GLfloat startx, GLfloat starty, GLfloat size);
void drawTrianglesStrip(GLfloat startx, GLfloat starty, GLfloat size);
void drawTrianglesFan(GLfloat startx, GLfloat starty, GLfloat size);
void drawTriangles(GLfloat startx, GLfloat starty, GLfloat size);
void drawHexagonFan(GLfloat startx, GLfloat starty, GLfloat size);
void drawPolygon(GLfloat startx, GLfloat starty, GLfloat size);
void drawPolygon2(GLfloat startx, GLfloat starty, GLfloat size);
void drawPolygon3(GLfloat startx, GLfloat starty, GLfloat size);
void drawPolygon4(GLfloat startx, GLfloat starty, GLfloat size);
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
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, 1);
        }
        glViewport(0, 0, WinWidth, WinHeight);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_programme);
        drawHexagonDots(-0.75f, 0.75f, 0.2f);
        drawHexagon(-0.25f, 0.75f, 0.2f);
        drawLineStrip(0.25f, 0.75f, 0.2f);
        drawLineLoop(0.75f, 0.75f, 0.2f);
        drawTriangles(-0.75f, 0.25f, 0.2f);
        drawTrianglesStrip(-0.25f, 0.25f, 0.2f);
        drawTrianglesFan(0.25f, 0.25f, 0.2f);
        drawHexagonFan(0.75f, 0.25f, 0.2f);
        drawPolygon(-0.75f, -0.25f, 0.2f);
        drawPolygon2(-0.25f, -0.25f, 0.2f);
        drawPolygon3(0.25f, -0.25f, 0.2f);
        drawPolygon4(0.75f, -0.25f, 0.2f);

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
void drawSmth(GLfloat* colors, GLfloat* points, GLfloat startx, GLfloat starty, GLfloat size, GLenum type, int n) {
    for (int i = 0; i < n * 3; i++)
        points[i] *= size;
    for (int i = 0; i < n * 3; i += 3)
        points[i] += startx;
    for (int i = 1; i < n * 3; i += 3)
        points[i] += starty;

    GLuint coords_vbo = 0;
    glGenBuffers(1, &coords_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
    glBufferData(GL_ARRAY_BUFFER, n * 3 * sizeof(float), points,
        GL_STATIC_DRAW);
    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, n * 3 * sizeof(float), colors,
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
    glBindVertexArray(vao);
    glDrawArrays(type, 0, n);
    glBindVertexArray(vao);
    glDeleteVertexArrays(1, &vao);
    glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
    glDeleteBuffers(1, &coords_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glDeleteBuffers(1, &colors_vbo);

}
void drawHexagonDots(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
    };
    GLfloat points[] = {
       0.0f, 1.0f, 0.0f,
       -0.86f, 0.5f, 0.0f,
       0.86f, 0.5f, 0.0f,
       0.86f, -0.5f, 0.0f,
       -0.86f, -0.5f, 0.0f,
       0.0f, -1.0f, 0.0f,
    };

    glEnable(GL_PROGRAM_POINT_SIZE);
    glPointSize(20);
    glEnable(GL_POINT_SMOOTH);
    drawSmth(colors, points, startx, starty, size, GL_POINTS, 6);
}

void drawHexagon(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
         0.0f, 1.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
          0.0f, 1.0f, 0.0f,
    };
    GLfloat points[] = {
       0.0f, 1.0f, 0.0f,
       -0.86f, 0.5f, 0.0f,
       -0.86f, -0.5f, 0.0f,
       0.0f, -1.0f, 0.0f,
       0.86f, -0.5f, 0.0f,
       0.86f, 0.5f, 0.0f,
    };
    glLineWidth(3);

    drawSmth(colors, points, startx, starty, size, GL_LINE_LOOP, 6);
}
void drawLineStrip(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
        0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };
    GLfloat points[] = {
       -1.0f, -0.1f, 0.0f,
       -0.5f, 1.0f, 0.0f,
       -0.3f, -1.0f, 0.0f,
       -0.2f, 0.3f, 0.0f,
       0.3f, 0.3f, 0.0f,
       0.3f, 1.0f, 0.0f,
       1.0f, -0.7f, 0.0f,
     



    };

    glLineWidth(3);
    drawSmth(colors, points, startx, starty, size, GL_LINE_STRIP, 7);
}
void drawLineLoop(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
        0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
    };
    GLfloat points[] = {
     -1.0f, -0.7f, 0.0f,
     -0.7f, 0.8f, 0.0f,
     0.3f, 1.0f, 0.0f,
     0.1f, 0.2f, 0.0f,
     1.0f, 0.4f, 0.0f,
     1.0f, -0.3f, 0.0f,
     0.1f, -0.3f, 0.0f,
     0.1f, -1.0f, 0.0f,
   //  -0.5f, -0.3f, 0.0f,

    };

    glLineWidth(3);
    drawSmth(colors, points, startx, starty, size, GL_LINE_LOOP, 8);
}
void drawTriangles(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
        0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
          0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
    };
    GLfloat points[] = {
      -1.0f, -0.7f, 0.0f,
     -0.7f, 0.8f, 0.0f,
     0.5f, 1.0f, 0.0f,

      -1.0f, -0.7f, 0.0f,
     -0.3f, 0.0f, 0.0f,
     0.2f, 0.0f, 0.0f,

          0.5f, 1.0f, 0.0f,
          0.4f, 0.2f, 0.0f,
          -0.7f, -0.3f, 0.0f,

        0.1f, 0.2f, 0.0f,
     1.0f, 0.4f, 0.0f,
     1.0f, -0.3f, 0.0f,

      1.0f, -0.3f, 0.0f,
       0.1f, -0.3f, 0.0f,
        -0.5f, 0.55f, 0.0f,

           0.4f, 0.3f, 0.0f,
           0.4f, -1.0f, 0.0f,
           -0.3f, 0.0f, 0.0f,


    };
    drawSmth(colors, points, startx, starty, size, GL_TRIANGLES,18);
}
void drawTrianglesStrip(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
       1.0f, 0.0f,0.0f,
       1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
       1.0f, 0.0f,0.0f,
       1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
          1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
         1.0f, 0.0f, 0.0f,
    };
    GLfloat points[] = {
       -1.0f, -0.7f, 0.0f,
     -0.7f, 0.8f, 0.0f,
     0.5f, 1.0f, 0.0f,

     0.3f, 0.4f, 0.0f,
     0.3f, -0.2f, 0.0f,
      1.0f, 0.5f, 0.0f,

      1.0f, -0.2f, 0.0f,


      0.3f, 0.4f, 0.0f,
      -0.2f, 0.6f, 0.0f,
      0.3f, -1.0f, 0.0f,

      0.3f, -1.0f, 0.0f,
      -0.2f, 0.4f, 0.0f,
            -0.3f, 0.0f, 0.0f,

               0.9f, 0.5f, 0.0f,
                -1.0f, -0.7f, 0.0f,

         //   -1.0f, -1.0f, 0.0f,




    };
    drawSmth(colors, points, startx, starty, size, GL_TRIANGLE_STRIP, 15);
}
void drawTrianglesFan(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
        0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
         0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
             0.0f, 0.0f, 1.0f,
    };
    GLfloat points[] = {
        -0.2f,0.0f,0.0f,
       -1.0f, 0.2f, 0.0f,
       -0.5f, 0.7f, 0.0f,
       0.0f, 0.3f, 0.0f,
       1.0f, 0.7f, 0.0f,
       1.0f, 0.0f, 0.0f,
       -0.2f, 0.0f, 0.0f,
        0.0f, -1.0f, 0.0f,
       -0.8f, -0.8f, 0.0f,
          -1.0f, 0.2f, 0.0f,
    };
    drawSmth(colors, points, startx, starty, size, GL_TRIANGLE_FAN, 10);
}

void drawHexagonFan(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
           0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
    };
    GLfloat points[] = {
        0.0f,0.0f,0.0f,
       0.0f, 1.0f, 0.0f,
       -0.86f, 0.5f, 0.0f,
       -0.86f, -0.5f, 0.0f,
       0.0f, -1.0f, 0.0f,
       0.86f, -0.5f, 0.0f,
       0.86f, 0.5f, 0.0f,
          0.0f, 1.0f, 0.0f,

    };
    drawSmth(colors, points, startx, starty, size, GL_TRIANGLE_FAN, 8);
}

void drawPolygon(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
     1.0f,0.0f,0.0f,
     1.0f,0.0f,0.0f,
     1.0f,0.0f,0.0f,

     0.0f,1.0f,0.0f,
     0.0f,1.0f,0.0f,
     0.0f,1.0f,0.0f,

        0.0f,0.0f,1.0f,
     0.0f,0.0f,1.0f,
     0.0f,0.0f,1.0f,

        1.0f,1.0f,0.0f,
     1.0f,1.0f,0.0f,
     1.0f,1.0f,0.0f,

          0.0f,1.0f,1.0f,
     0.0f,1.0f,1.0f,
     0.0f,1.0f,1.0f,

      1.0f,0.0f,1.0f,
     1.0f,0.0f,1.0f,
     1.0f,0.0f,1.0f,

           1.0f,1.0f,1.0f,
     1.0f,1.0f,1.0f,
     1.0f,1.0f,1.0f,

     0.5f,0.0f,0.0f,
     0.5f,0.0f,0.0f,
     0.5f,0.0f,0.0f,
    };
    GLfloat points[] = {
     -1.0f,-1.0f,0.0f,
     -0.2f,-1.0f,0.0f,
     -0.8f,-0.8f,0.0f,

     -1.0f,-1.0f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.8f,-0.8f,0.0f,

     -0.2f,0.2f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.8f,-0.8f,0.0f,

     -0.2f,0.2f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.3f,0.5f,0.0f,

     -0.2f,0.2f,0.0f,
     0.8f,1.0f,0.0f,
     -0.3f,0.5f,0.0f,

      -0.2f,0.2f,0.0f,
     0.8f,1.0f,0.0f,
     0.2f,0.2f,0.0f,

     1.0f,-1.0f,0.0f,
     0.8f,1.0f,0.0f,
     0.2f,0.2f,0.0f,

          1.0f,-1.0f,0.0f,
     0.2f,-1.0f,0.0f,
     0.2f,0.2f,0.0f,
    };
    drawSmth(colors, points, startx, starty, size, GL_TRIANGLES, 24);
}

void drawPolygon2(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
  1.0f,0.0f,0.0f,
  1.0f,0.0f,0.0f,
  1.0f,0.0f,0.0f,

  0.0f,1.0f,0.0f,
  0.0f,1.0f,0.0f,
  0.0f,1.0f,0.0f,

     0.0f,0.0f,1.0f,
  0.0f,0.0f,1.0f,
  0.0f,0.0f,1.0f,

     1.0f,1.0f,0.0f,
  1.0f,1.0f,0.0f,
  1.0f,1.0f,0.0f,

       0.0f,1.0f,1.0f,
  0.0f,1.0f,1.0f,
  0.0f,1.0f,1.0f,

   1.0f,0.0f,1.0f,
  1.0f,0.0f,1.0f,
  1.0f,0.0f,1.0f,

        1.0f,1.0f,1.0f,
  1.0f,1.0f,1.0f,
  1.0f,1.0f,1.0f,

  0.5f,0.0f,0.0f,
  0.5f,0.0f,0.0f,
  0.5f,0.0f,0.0f,
    };
    GLfloat points[] = {
     -1.0f,-1.0f,0.0f,
     -0.2f,-1.0f,0.0f,
     -0.8f,-0.8f,0.0f,

     -1.0f,-1.0f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.8f,-0.8f,0.0f,

     -0.2f,0.2f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.8f,-0.8f,0.0f,

     -0.2f,0.2f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.3f,0.5f,0.0f,

     -0.2f,0.2f,0.0f,
     0.8f,1.0f,0.0f,
     -0.3f,0.5f,0.0f,

      -0.2f,0.2f,0.0f,
     0.8f,1.0f,0.0f,
     0.2f,0.2f,0.0f,

     1.0f,-1.0f,0.0f,
     0.8f,1.0f,0.0f,
     0.2f,0.2f,0.0f,

          1.0f,-1.0f,0.0f,
     0.2f,-1.0f,0.0f,
     0.2f,0.2f,0.0f,
    };
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

    drawSmth(colors, points, startx, starty, size, GL_TRIANGLES, 24);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void drawPolygon3(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
  1.0f,0.0f,0.0f,
  1.0f,0.0f,0.0f,
  1.0f,0.0f,0.0f,

  0.0f,1.0f,0.0f,
  0.0f,1.0f,0.0f,
  0.0f,1.0f,0.0f,

     0.0f,0.0f,1.0f,
  0.0f,0.0f,1.0f,
  0.0f,0.0f,1.0f,

     1.0f,1.0f,0.0f,
  1.0f,1.0f,0.0f,
  1.0f,1.0f,0.0f,

       0.0f,1.0f,1.0f,
  0.0f,1.0f,1.0f,
  0.0f,1.0f,1.0f,

   1.0f,0.0f,1.0f,
  1.0f,0.0f,1.0f,
  1.0f,0.0f,1.0f,

        1.0f,1.0f,1.0f,
  1.0f,1.0f,1.0f,
  1.0f,1.0f,1.0f,

  0.5f,0.0f,0.0f,
  0.5f,0.0f,0.0f,
  0.5f,0.0f,0.0f,
    };
    GLfloat points[] = {
     -1.0f,-1.0f,0.0f,
     -0.2f,-1.0f,0.0f,
     -0.8f,-0.8f,0.0f,

     -1.0f,-1.0f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.8f,-0.8f,0.0f,

     -0.2f,0.2f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.8f,-0.8f,0.0f,

     -0.2f,0.2f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.3f,0.5f,0.0f,

     -0.2f,0.2f,0.0f,
     0.8f,1.0f,0.0f,
     -0.3f,0.5f,0.0f,

      -0.2f,0.2f,0.0f,
     0.8f,1.0f,0.0f,
     0.2f,0.2f,0.0f,

     1.0f,-1.0f,0.0f,
     0.8f,1.0f,0.0f,
     0.2f,0.2f,0.0f,

          1.0f,-1.0f,0.0f,
     0.2f,-1.0f,0.0f,
     0.2f,0.2f,0.0f,
    };

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_LINE);

    drawSmth(colors, points, startx, starty, size, GL_TRIANGLES, 24);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}

void drawPolygon4(GLfloat startx, GLfloat starty, GLfloat size) {
    GLfloat colors[] = {
  1.0f,0.0f,0.0f,
  1.0f,0.0f,0.0f,
  1.0f,0.0f,0.0f,

  0.0f,1.0f,0.0f,
  0.0f,1.0f,0.0f,
  0.0f,1.0f,0.0f,

     0.0f,0.0f,1.0f,
  0.0f,0.0f,1.0f,
  0.0f,0.0f,1.0f,

     1.0f,1.0f,0.0f,
  1.0f,1.0f,0.0f,
  1.0f,1.0f,0.0f,

       0.0f,1.0f,1.0f,
  0.0f,1.0f,1.0f,
  0.0f,1.0f,1.0f,

   1.0f,0.0f,1.0f,
  1.0f,0.0f,1.0f,
  1.0f,0.0f,1.0f,

        1.0f,1.0f,1.0f,
  1.0f,1.0f,1.0f,
  1.0f,1.0f,1.0f,

  0.5f,0.0f,0.0f,
  0.5f,0.0f,0.0f,
  0.5f,0.0f,0.0f,
    };
    GLfloat points[] = {
     -1.0f,-1.0f,0.0f,
     -0.2f,-1.0f,0.0f,
     -0.8f,-0.8f,0.0f,

     -1.0f,-1.0f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.8f,-0.8f,0.0f,

     -0.2f,0.2f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.8f,-0.8f,0.0f,

     -0.2f,0.2f,0.0f,
     -1.0f,0.8f,0.0f,
     -0.3f,0.5f,0.0f,

     -0.2f,0.2f,0.0f,
     0.8f,1.0f,0.0f,
     -0.3f,0.5f,0.0f,

      -0.2f,0.2f,0.0f,
     0.8f,1.0f,0.0f,
     0.2f,0.2f,0.0f,

     1.0f,-1.0f,0.0f,
     0.8f,1.0f,0.0f,
     0.2f,0.2f,0.0f,

          1.0f,-1.0f,0.0f,
     0.2f,-1.0f,0.0f,
     0.2f,0.2f,0.0f,
    };
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    drawSmth(colors, points, startx, starty, size, GL_TRIANGLES, 24);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}
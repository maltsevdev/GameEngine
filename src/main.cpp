#include <iostream>

#include "../include/glad/glad.h" 
#include <GLFW/glfw3.h>
#include "Render/ShaderProgram/ShaderProgram.h"
#include "Render/VBO/VBO.h"

int windowSizeX = 640;
int windowSizeY = 480;

GLfloat points[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};

GLfloat colors[] = {
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f
};

const char* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 1.0);"
"}";

const char* fragment_shader = 
"#version 460\n"
"in vec3 color;"
"out vec4 fragment_color;"
"void main() {"
"   fragment_color = vec4(color, 1.0);"
"}";

void glfwWindowSizeCallback(GLFWwindow* pWindow, int sizeX, int sizeY)
{
    windowSizeX = sizeX;
    windowSizeY = sizeY;
    glViewport(0, 0, windowSizeX, windowSizeY); 
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scanCode, int action, int mode)
{
    if (key == static_cast<int>(GLFW_KEY_ESCAPE) && action == static_cast<int>(GLFW_PRESS))
    {
        glfwSetWindowShouldClose(pWindow, static_cast<int>(GL_TRUE)); 
    } 
}

int main(void)
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
     
    GLFWwindow* pWindow = glfwCreateWindow(windowSizeX, windowSizeY, "Game Engine", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "Windows doesn't create" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    glfwMakeContextCurrent(pWindow);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Can't load glad" << std::endl;
        return -1;
    }

    std::cout << "Render: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGl version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(0, 1, 1, 1);

    std::string vertexShader(vertex_shader);
    std::string fragmentShader(fragment_shader);

    Render::ShaderProgram shaderProgram(vertexShader, fragmentShader);
    if (!shaderProgram.isCompiled())
    {
        std::cerr << "Can't create shader program" << std::endl;
        return -1;
    }

    GLuint points_vbo = 0;
    Render::VBO vbo_points(1, points_vbo, sizeof(points), points, GL_STATIC_DRAW);
    if (!vbo_points.isCreate())
    {
        std::cerr << "VBO points can't create" << std::endl;
        return -1;
    }

    GLuint colors_vbo = 0;
    Render::VBO vbo_colors(1, colors_vbo, sizeof(colors), colors, GL_STATIC_DRAW);
    if (!vbo_colors.isCreate())
    {
        std::cerr << "VBO colors can't work" << std::endl;
        return -1;
    }

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    while (!glfwWindowShouldClose(pWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.useProgram();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(pWindow);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

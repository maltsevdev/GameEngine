#include "glfwCallback.h"

namespace Callback
{
    void glfwWindowSizeCallback(GLFWwindow* pWindow, int sizeX, int sizeY)
    {
        glViewport(0, 0, sizeX, sizeY);
    }

    void glfwKeyCallback(GLFWwindow* pWindow, int key, int scanCode, int action, int mode)
    {
        if (key == static_cast<int>(GLFW_KEY_ESCAPE) && action == static_cast<int>(GLFW_PRESS))
        {
            glfwSetWindowShouldClose(pWindow, static_cast<int>(GL_TRUE));
        }
    }
}

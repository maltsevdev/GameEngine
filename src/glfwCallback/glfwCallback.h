#ifndef GAMEENGINE_GLFWCAALLBACK_H
#define GAMEENGINE_GLFWCAALLBACK_H

#pragma once

#include "../../include/glad/glad.h"
#include <GLFW/glfw3.h>

namespace Callback
{
    void glfwWindowSizeCallback(GLFWwindow* pWindow, int sizeX, int sizeY);
    void glfwKeyCallback(GLFWwindow* pWindow, int key, int scanCode, int action, int mode);
}
#endif //GAMEENGINE_GLFWCAALLBACK_H

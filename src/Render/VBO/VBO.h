#pragma once  

#include <iostream>

#include "../../../include/glad/glad.h"

namespace Render
{
    class VBO
    {
    public:
        VBO(int quantityBuffers, GLuint& VBO, size_t size, GLfloat data[], GLenum usage);
        ~VBO();

        VBO() = delete;
        VBO(int, GLuint&, GLfloat, GLenum) = delete;
        VBO(VBO&) = delete;
        VBO(VBO&&) = delete;
        VBO operator=(const VBO&) = delete;

        bool isCreate();
    private:
        bool isCreateBool = false;
    };
}

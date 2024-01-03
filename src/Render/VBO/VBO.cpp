#include "VBO.h"

namespace Render
{
    VBO::VBO(int quantityBuffers, GLuint& VBO, size_t size, GLfloat data[], GLenum usage)
    {   
        glGenBuffers(quantityBuffers, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
        if (VBO != 0)
        {
            std::cout << "VBO create" << std::endl;
            isCreateBool = true;
        }
    }

    bool VBO::isCreate()
    {
        return isCreateBool;
    }

    VBO::~VBO()
    {
        std::cout << "VBO is kill" << std::endl;        
    }
}

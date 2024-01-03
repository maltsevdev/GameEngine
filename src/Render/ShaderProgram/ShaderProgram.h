#pragma once

#include "../../../include/glad/glad.h"

#include <string>
#include <iostream>

namespace Render 
{ 
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

        ShaderProgram() = delete;
        ShaderProgram(ShaderProgram&) = delete;
        ShaderProgram& operator=(const ShaderProgram&) = delete;

        ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
        ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
        
        ~ShaderProgram();

        bool isCompiled() const;  
        void useProgram() const;
    private:
        bool createShader(const std::string& source, const GLuint shaderType, GLuint& shaderID);
        bool shaderLinkProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID, GLuint shaderProgramIDs);

        bool compiledStatus = false;
        GLuint shaderProgramID = 0;
    };
}


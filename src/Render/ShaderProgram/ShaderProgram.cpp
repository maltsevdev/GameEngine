#include "ShaderProgram.h"
       
namespace Render 
{
    ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLuint vertexShaderID;
        if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
        {
            std::cerr << "ERROR:VERTEXSHADER dont compile" << std::endl;
            return;         
        }

        GLuint fragmentShaderID;
        if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
        {
            std::cerr << "ERROR:FRAGMENTSHADER don't compile" << std::endl;
            glDeleteShader(vertexShaderID);
            return;
        }

        shaderProgramID = glCreateProgram();
        glAttachShader(shaderProgramID, vertexShaderID);
        glAttachShader(shaderProgramID, fragmentShaderID);
        glLinkProgram(shaderProgramID);

        GLint success;
        glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderProgramID, 1024, nullptr, infoLog);
            std::cerr << "ERROR:LINKSHADER shader doesn't link: " << infoLog << std::endl;  
            compiledStatus = false;
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
        compiledStatus = true;

   }

    ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
    {
        shaderProgramID = shaderProgram.shaderProgramID; 
        compiledStatus = shaderProgram.compiledStatus;
        
        shaderProgram.shaderProgramID = 0;
        shaderProgram.compiledStatus = false;
    }


    ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept 
    {
        glDeleteProgram(shaderProgramID);
        shaderProgramID = shaderProgram.shaderProgramID;
        compiledStatus = shaderProgram.compiledStatus;

        shaderProgram.shaderProgramID = 0;
        shaderProgram.compiledStatus = false;
        return *this;
    }

    ShaderProgram::~ShaderProgram()
    {
        glDeleteProgram(shaderProgramID); 
    }

    bool ShaderProgram::isCompiled() const 
    {
        return compiledStatus;
    } 
      
    void ShaderProgram::useProgram() const
    {
        glUseProgram(shaderProgramID);
    }

    bool ShaderProgram::createShader(const std::string &source, const GLuint shaderType, GLuint& shaderID)
    {
        shaderID = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shaderID, 1, &code, nullptr); 
        glCompileShader(shaderID);
        
        GLint success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER error compile shader: " << infoLog;
            return false; 
        }
        return true;
    }
}  


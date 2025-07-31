#include "Shader.hpp"
#include <iostream>
#include <string>
#include <fstream>

namespace graphics
{
    namespace renderer
    {
        Shader::Shader(const char * shaderFilePath,GLenum shaderType)
        : _shaderType{shaderType}, _shaderFilePath{shaderFilePath}
        {
            std::cout << "Shader Type: " << _shaderType << ", constructor called: " << shaderFilePath << std::endl;
            auto result = loadFromFile();
            if(!result)
            {
                throw std::runtime_error("Nao foi possivel abrir o arquivo");
            }

            _shaderSource = *result;
            _shader = glCreateShader(shaderType);
            glShaderSource(_shader,1,&_shaderSource,NULL);
            if(!compileShader())
            {
                throw std::runtime_error("Error ao compilador o shader do tipo " +
                                        shaderType + std::string(": \n") + _infoLog);
            }
        }

        bool Shader::compileShader()
        {
            glCompileShader(_shader);
            GLint sucess;
            glGetShaderiv(_shader,GL_COMPILE_STATUS,&sucess);
            if (!sucess)
            {
                glGetShaderInfoLog(_shader, sizeof(_infoLog), NULL, _infoLog);
                glDeleteShader(_shader);
                _shader = 0;
                return false;
            }
            return true;
        }

        GLuint Shader::getShaderId() const
        {
            return _shader;
        }

        Shader::~Shader()
        {
            std::cout << "Shader Type: " << _shaderType << ", destructor called: " << _shaderFilePath << std::endl;
            glDeleteShader(_shader);
            _shader = 0;
        }
        std::optional<const char*> Shader::loadFromFile()
        {
            std::string line;
            std::string content;
            std::ifstream fileStream(_shaderFilePath,std::ios::in);
            if (!fileStream.is_open()) 
            {
                std::cerr << "Could not read file " << _shaderFilePath << ". File does not exist." << std::endl;
                return std::nullopt;
            }
            while (!fileStream.eof()) 
            {
                std::getline(fileStream, line);
                content.append(line + "\n");
            }
            fileStream.close();

            return content.c_str();
        }
    }
}
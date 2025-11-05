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
            if(result && result.value().empty())
                throw std::runtime_error("Shader file carregado vazio: " + std::string(shaderFilePath));

            _shaderSource = result.value();
            const char * src = _shaderSource.c_str();
            _shader = glCreateShader(shaderType);
            glShaderSource(_shader,1,&src,NULL);
            if(!compileShader())
            {
                std::string typeStr = (_shaderType == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT");
                throw std::runtime_error("Shader compilation failed (" + typeStr + "):\n" + std::string(_infoLog));
            }
        }

        bool Shader::compileShader()
        {
            glCompileShader(_shader);
            GLint sucess;
            glGetShaderiv(_shader,GL_COMPILE_STATUS,&sucess);
            if (!sucess)
            {
                glGetShaderInfoLog(_shader, 512, NULL, _infoLog);
                glDeleteShader(_shader);
                _shader = 0;
                return false;
            }
            std::cout << "Shader: " << _shader << " compiled" << std::endl;
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
        std::optional<std::string> Shader::loadFromFile()
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

            return content;
        }
    }
}

#pragma once
#include <glad/glad.h>
#include <optional>
#include <string>
namespace graphics
{
    namespace renderer
    {
        class Shader
        {
            public:
                Shader(const char * shaderFilePath,GLenum shaderType);
                GLuint getShaderId() const;
                ~Shader();
            private:
                bool compileShader();
                std::optional<std::string> loadFromFile();
            private:
                std::string _shaderSource;
                GLenum _shaderType;
                const char * _shaderFilePath;
                //OpenGL shader id
                GLuint _shader;
                GLchar _infoLog[512];
        };
    } // namespace renderer
} // namespace graphics

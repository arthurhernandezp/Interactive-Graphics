#pragma once
#include <glad/glad.h>
#include <optional>
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
                std::optional<const char*> loadFromFile();
            private:
                const GLchar* _shaderSource;
                GLenum _shaderType;
                const char * _shaderFilePath;
                //OpenGL shader id
                GLuint _shader;
                GLchar _infoLog[1024];
        };
    } // namespace renderer
} // namespace graphics

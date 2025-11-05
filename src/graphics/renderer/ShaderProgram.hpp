#pragma once
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr

#include <vector>
#include <memory>
namespace graphics
{
    namespace renderer
    {
        class Shader;

        class ShaderProgram
        {
            public:
                ShaderProgram(const char * vertexShaderFilePath,
                const char * fragmentshaderFilePath);
                ~ShaderProgram();
                GLuint& getProgramId();

                void use();
                GLint getUniformVarPosition(const char * uniformVariable);
                GLuint getAttribLocation(const char * vertexAttribute) const;
                void sendUniform(const char * uniformVariable, glm::mat4 &matrix4);
                void sendUniform(const char * uniformVariable, glm::mat3 &matrix3);
                void sendUniform(const char * uniformVariable, float &vData);
                void sendUniform(const char * uniformVariable, glm::vec3 &vec);
                void sendUniform(const char * uniformVariable, int value);

                void recompileShaders(GLFWwindow* window);
            private:
                void attachShaders() const;
                void linkShaders();
            private:
                GLuint _program;
                std::unique_ptr<Shader> _vs;
                const char * _vsFilePath;
                std::unique_ptr<Shader> _fs;
                const char * _fsFilePath;
                GLchar _infoLog[512]{};

                bool recompileButtonClick = false;
        };
    } // namespace renderer
} // namespace graphics

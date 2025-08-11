#include "ShaderProgram.hpp"
#include "Shader.hpp"
#include <iostream>
#include <memory>                   //unique_ptr

namespace graphics
{
    namespace renderer
    {
        ShaderProgram::ShaderProgram(const char *vertexShaderFilePath, const char *fragmentshaderFilePath)
        {
            std::cout << "Shader Program Constructor called" << '\n';
            try{
                _vs = std::make_unique<graphics::renderer::Shader>(vertexShaderFilePath,GL_VERTEX_SHADER);

                _fs = std::make_unique<graphics::renderer::Shader>(fragmentshaderFilePath,GL_FRAGMENT_SHADER);

                _program = glCreateProgram();
                attachShaders();
                linkShaders();
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        ShaderProgram::~ShaderProgram()
        {
            std::cout << "ShaderProgram destructor called" << '\n';
            glDetachShader(_program,_vs->getShaderId());
            glDetachShader(_program,_fs->getShaderId());
        }

        GLuint &ShaderProgram::getProgramId()
        {
            return _program;
        }

        void ShaderProgram::use()
        {
            glUseProgram(_program);
        }

        GLint ShaderProgram::getUniformVarPosition(const char * uniformVariable)
        {
            return glGetUniformLocation(_program, uniformVariable);
        }

        GLuint ShaderProgram::getAttribLocation(const char *vertexAttribute) const
        {
            return glGetAttribLocation(_program,vertexAttribute);
        }

        void ShaderProgram::sendUniformMat4(const char *uniformVariable,glm::mat4 &matrix)
        {
            GLint uniformVarLoc = getUniformVarPosition(uniformVariable);
            if (uniformVarLoc != -1){
                glUniformMatrix4fv(uniformVarLoc, 1, GL_FALSE, glm::value_ptr(matrix));
            } else{
                std::cerr << "Uniform " << uniformVariable << " não encontrado!" << std::endl;
            }
        }

        void ShaderProgram::sendUniformFloat(const char *uniformVariable, float &vData)
        {
            GLint uniformVarLoc = getUniformVarPosition(uniformVariable);
            if (uniformVarLoc != -1){
                glUniform1f(uniformVarLoc,vData);
            } else{
                std::cerr << "Uniform " << uniformVariable << " não encontrado!" << std::endl;
            }
        }

        void ShaderProgram::attachShaders() const
        {
            glAttachShader(_program,_vs->getShaderId());
            glAttachShader(_program,_fs->getShaderId());
        }

        void ShaderProgram::linkShaders()
        {
            glLinkProgram(_program);
            GLint success;
            glGetProgramiv(_program, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(_program, 512, NULL, _infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << _infoLog << std::endl;
            }
        }

    } // namespace renderer
} // namespace graphics

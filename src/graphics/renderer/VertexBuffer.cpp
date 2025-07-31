#include "VertexBuffer.hpp"
#include <iostream>
namespace graphics
{
    namespace renderer
    {
        VertexBufferObject::VertexBufferObject()
        {
            generateBuffer();
        }
        
        VertexBufferObject::~VertexBufferObject()
        {
        }

        void VertexBufferObject::sendData(GLuint attributeLocation,GLint numberOfElements,GLenum dataType) const
        {
            bindBuffer();
            glEnableVertexAttribArray(attributeLocation);
            glVertexAttribPointer(
                attributeLocation,numberOfElements,dataType,
                GL_FALSE,0,(void*)0
            );
            std::cout << "Enviando os dados do VBO para o Vertex Shader" << '\n';
        }

        void VertexBufferObject::bindBuffer() const
        {
            glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        }

        void VertexBufferObject::generateBuffer()
        {
            glGenBuffers(1,&_vbo);
        }
        void VertexBufferObject::receiveData(const float* data, size_t count, GLenum dataUsage)
        {
            bindBuffer();
            glBufferData(GL_ARRAY_BUFFER,
                    count,
                    data,
                    dataUsage);
            std::cout << "Criando VBO e colocando os dados de positions no buffer" << '\n';

        }
    } // namespace renderer
    
} // namespace graphics


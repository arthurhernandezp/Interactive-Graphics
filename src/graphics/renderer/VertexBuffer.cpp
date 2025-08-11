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
            glDeleteBuffers(1,&_vbo);
        }

        void VertexBufferObject::bindBuffer() const
        {
            glBindBuffer(GL_ARRAY_BUFFER,_vbo);
        }

        void VertexBufferObject::unbindBuffer() const
        {
            glBindBuffer(GL_ARRAY_BUFFER,0);
        }

        void VertexBufferObject::generateBuffer()
        {
            glGenBuffers(1,&_vbo);
        }
        void VertexBufferObject::receiveData(std::vector<float> &data, GLenum dataUsage)
        {
            bindBuffer();
            glBufferData(GL_ARRAY_BUFFER,
                    data.size() * sizeof(float),
                    data.data(),
                    dataUsage);
            std::cout << "Criando VBO e colocando os dados de positions no buffer" << '\n';
            unbindBuffer();
        }
    } // namespace renderer

} // namespace graphics

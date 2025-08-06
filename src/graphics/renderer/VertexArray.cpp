#include "VertexArray.hpp"

namespace graphics
{
    namespace renderer
    {
        VertexArrayObject::VertexArrayObject()
        {
            glGenVertexArrays(1, &_ID);
        }

        VertexArrayObject::~VertexArrayObject()
        {
            glDeleteVertexArrays(1, &_ID);
        }

        // Links a VBO to the VAO using a certain layout
        void VertexArrayObject::LinkVBO(VertexBufferObject& VBO, GLuint layout)
        {
            VBO.bindBuffer();
            glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
            glEnableVertexAttribArray(layout);
            VBO.unbindBuffer();
        }

        // Binds the VAO
        void VertexArrayObject::bindBuffer()
        {
            glBindVertexArray(_ID);
        }

        // Unbinds the VAO
        void VertexArrayObject::unbindBuffer()
        {
            glBindVertexArray(0);
        }

    } // namespace renderer
} // namespace graphics

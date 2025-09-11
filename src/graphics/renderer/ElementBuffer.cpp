#include "ElementBuffer.hpp"

namespace graphics
{
    namespace renderer
    {
        ElementBufferObject::ElementBufferObject(int *indices, GLsizeiptr size)
        {
            glGenBuffers(1, &_ID);
            bindBuffer();
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
        }

        ElementBufferObject::~ElementBufferObject()
        {
            glDeleteBuffers(1, &_ID);
        }

        void ElementBufferObject::bindBuffer()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ID);
        }

        void ElementBufferObject::unbindBuffer()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
        GLuint ElementBufferObject::getEBOId()
        {
            return _ID;
        }
    } // namespace renderer
} // namespace graphics

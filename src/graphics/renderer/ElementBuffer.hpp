#pragma once
#include<glad/glad.h>

namespace graphics
{
    namespace renderer
    {
        class ElementBufferObject
        {
        public:
            // Constructor that generates a Elements Buffer Object and links it to indices
            ElementBufferObject(int* indices, GLsizeiptr size);
            ~ElementBufferObject();
            // Binds the EBO
            void bindBuffer();
            // Unbinds the EBO
            void unbindBuffer();
            GLuint getEBOId();
        private:

        private:
            // ID reference of Elements Buffer Object
            GLuint _ID;
        };
    } // namespace renderer
} // namespace grephics

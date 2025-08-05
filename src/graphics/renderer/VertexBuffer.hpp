#pragma once
#include <glad/glad.h>

namespace graphics
{
    namespace renderer
    {
        class VertexBufferObject
        {
            public:
                VertexBufferObject();
                ~VertexBufferObject();
                void receiveData(const float* data, size_t count, GLenum dataUsage);
                // @todo change sendData name function to tell how OpenGL will interpreter the data 
                void sendData(GLuint attribute,GLint numberOfElements,GLenum dataType) const;
                void bindBuffer() const;

            private:
                void generateBuffer();
            private:
                GLuint _vbo;
        };
    }//namespace renderer  
} // namespace graphics

#pragma once
#include <glad/glad.h>
#include <vector>
namespace graphics
{
    namespace renderer
    {
        class VertexBufferObject
        {
            public:
                VertexBufferObject();
                ~VertexBufferObject();
                void receiveData(std::vector<float> data, GLenum dataUsage);

                void bindBuffer() const;
                void unbindBuffer() const;

            private:
                void generateBuffer();
            private:
                GLuint _vbo;
        };
    }//namespace renderer
} // namespace graphics

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
                void receiveData(std::vector<float> &data, GLenum dataUsage);

                void bindBuffer() const;
                void unbindBuffer() const;

                unsigned int getLayout() const;
                void setLayout(unsigned int attribLocation);
            private:
                void generateBuffer();
            private:
                GLuint _vbo;
                unsigned int _layout;
        };
    }//namespace renderer
} // namespace graphics

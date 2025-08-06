#pragma once
#include "VertexBuffer.hpp"
#include<glad/glad.h>
namespace graphics
{
    namespace renderer
    {
        class VertexArrayObject
            {
            public:
                // Constructor that generates a VAO ID
                VertexArrayObject();
                ~VertexArrayObject();
                // Links a VBO to the VAO using a certain layout
                void LinkVBO(VertexBufferObject& VBO, GLuint layout);
                void bindBuffer();
                void unbindBuffer();
                GLuint getVAOId();
            private:

            private:
                // ID reference for the Vertex Array Object
                GLuint _ID;
            };
    } // namespace renderer

} // namespace graphics

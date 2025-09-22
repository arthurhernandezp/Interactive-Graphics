#pragma once
#include <vector>
#include <memory>

#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/VertexArray.hpp"
#include "graphics/renderer/ElementBuffer.hpp"

#include <glm/glm.hpp>

namespace graphics
{
    namespace lighting
    {
        class Light
        {
            public:
                Light();
                ~Light();
                void draw() const;
                glm::vec3& getLightSource();

            private:
                void createCubeLight();
                void createCubeIndices();
            private:
                float cubeSize = 2.0f; // metade do comprimento da aresta do cubo

                std::vector<float> cubeVertices;
                std::vector<int> cubeIndices;
                std::shared_ptr<graphics::renderer::VertexBufferObject> _vboPos;
                std::shared_ptr<graphics::renderer::VertexArrayObject> _vao;
                std::shared_ptr<graphics::renderer::ElementBufferObject> _ebo;

                glm::vec3 _lightSource = glm::vec3(0.0f, 10.0f, 3.0f);
        };
    } // namespace lighting

} // namespace graphics

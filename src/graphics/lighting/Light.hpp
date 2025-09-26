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
                glm::vec3 lightSource = glm::vec3(0.0f, 20.0f, 3.0f);

                float intensity = 0.5;
                float ambientIntensity = 0.1;
                float specularStrength = 0.9;

            private:
                void createCubeLight();
                void createCubeIndices();
            private:
                float cubeSize = 1.0f;
                std::vector<float> cubeVertices;
                std::vector<int> cubeIndices;
                std::shared_ptr<graphics::renderer::VertexBufferObject> _vboPos;
                std::shared_ptr<graphics::renderer::VertexArrayObject> _vao;
                std::shared_ptr<graphics::renderer::ElementBufferObject> _ebo;

        };
    } // namespace lighting

} // namespace graphics

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

            private:
                std::shared_ptr<graphics::renderer::VertexBufferObject> _vboPos;
                std::shared_ptr<graphics::renderer::VertexArrayObject> _vao;
                std::vector<float> _directionalLightVertex{10.0f,  0.0f,  0.0f,
                                                     0.0f,  0.0f, 0.0f,
                                                     -10.f, 0.0f, 0.0f,
                                                     0.0f, -10.0f, 0.0f,
                                                    0.0f,  0.0f, 0.0f,
                                                    0.0f,  10.0f, 0.0f,
                                                    0.0f,  0.0f, 10.0f,
                                                    0.0f,  0.0f, 0.0f,
                                                    0.0f,  0.0f, -10.0f,
                                                    0.0f,0.0f,0.0f,
                                                    0.0f, 10.0f, 10.0f,
                                                    0.0f, 10.0f, 10.0f
                                                    };
                glm::vec3 _lightSource = glm::vec3(0.0f, 10.0f, 10.0f);
        };
    } // namespace lighting

} // namespace graphics

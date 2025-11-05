#pragma once
#include <vector>
#include <memory>
#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/VertexArray.hpp"

namespace graphics
{
    namespace geometry
    {
        class Triangle
        {
            public:
                Triangle() = default;
                Triangle(std::vector<float> v,std::vector<float>vn = {},std::vector<float>vt = {});
                ~Triangle();

                void draw();
            private:

            private:
                std::shared_ptr<graphics::renderer::VertexArrayObject> _vao;
                std::shared_ptr<graphics::renderer::VertexBufferObject> _vbo;
                std::shared_ptr<graphics::renderer::VertexBufferObject> _vboNormal;
                std::shared_ptr<graphics::renderer::VertexBufferObject> _vboTexCoords;

                std::vector<float> _normal{};

                std::vector<float> _vertices{   -0.5f, -0.5f, 0.0f,
                                                0.5f, -0.5f, 0.0f,
                                                0.0f,  0.5f, 0.0f};

                std::vector<float> _texCoords{1.0f,1.0f,
                                              1.0f,0.0f,
                                              0.0f,0.0f,
                                              0.0f,1.0f};
        };
    } // namespace geometry
    
} // namespace graphics

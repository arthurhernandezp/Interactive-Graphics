#pragma once
#include <vector>
#include <memory>       // shared_ptr

#include <fstream>      // read obj file
#include <sstream>

#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/VertexArray.hpp"
#include "graphics/renderer/ElementBuffer.hpp"

namespace graphics
{
    namespace mesh
    {
        class Mesh
        {
            public:
                Mesh(const std::string &objFilePath);
                void draw() const;
                void drawPointCloud() const;

                ~Mesh();
            private:
                void loadObj();
            private:
                std::string _objFilePath;

                std::shared_ptr<graphics::renderer::VertexBufferObject> _vboPos;
                std::shared_ptr<graphics::renderer::VertexBufferObject> _vboNormal;

                std::shared_ptr<graphics::renderer::VertexArrayObject> _vao;
                std::shared_ptr<graphics::renderer::ElementBufferObject> _ebo;

                std::vector<float> _vertices;
                std::vector<int> _indices;
                std::vector<float> _normal;
        };
    } // namespace mesh
} // namespace graphics

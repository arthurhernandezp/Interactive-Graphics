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
                Mesh(const std::vector<float>& vertices,
                   const std::vector<float>& normals,
                   const std::vector<float>& texCoords,
                   const std::vector<int>& indices);
                ~Mesh();
                void swapRenderMode();
                void draw() const;
                enum
                {
                    VERTICES_ONLY = GL_POINTS,
                    LINES = GL_LINES,
                    FULLMESH = GL_TRIANGLES
                };

                int _renderMode = FULLMESH;

            private:

            private:

                std::string _objFilePath;

                std::shared_ptr<graphics::renderer::VertexBufferObject> _vboPos;
                std::shared_ptr<graphics::renderer::VertexBufferObject> _vboNormal;
                std::shared_ptr<graphics::renderer::VertexBufferObject> _vboTexCoords;

                std::shared_ptr<graphics::renderer::VertexArrayObject> _vao;
                std::shared_ptr<graphics::renderer::ElementBufferObject> _ebo;

                std::vector<float> _vertices;
                std::vector<int> _indices;
                std::vector<float> _normal;
                std::vector<float> _texCoords;
        };
    } // namespace mesh
} // namespace graphics

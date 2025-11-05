#pragma once
#include <string>
#include <memory>
#include "graphics/mesh/Mesh.hpp" 

namespace graphics
{
    namespace mesh
    {
        class MeshLoader
        {
        public:
            static std::shared_ptr<mesh::Mesh> loadObj(const std::string& objFilePath);
        };

    } // namespace mesh
} // namespace graphics

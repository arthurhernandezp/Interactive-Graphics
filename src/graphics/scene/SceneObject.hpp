#pragma once
#include "core/Transform.hpp"

#include <memory>

namespace graphics
{
    namespace mesh { class Mesh; }

    namespace scene
    {
        class SceneObject
        {
            public:
                SceneObject() = default;

                Transform transform;

                std::shared_ptr<graphics::mesh::Mesh> getMesh() const;
                void setMesh(std::shared_ptr<graphics::mesh::Mesh> mesh);
            private:

            private:    
                std::shared_ptr<graphics::mesh::Mesh> _mesh;
        };
    } // namespace scene
    
} // namespace graphics

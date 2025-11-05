#pragma once
#include "core/Transform.hpp"
#include <glm/glm.hpp>

#include <memory>

namespace graphics
{
    namespace mesh { class Mesh; }
    namespace material { class Material; }

    namespace scene
    {
        class SceneObject
        {
            public:
                SceneObject() = default;
                SceneObject(glm::vec3 objColor);

                Transform transform;

                std::shared_ptr<graphics::mesh::Mesh> getMesh() const;
                void setMesh(std::shared_ptr<graphics::mesh::Mesh> mesh);

                std::shared_ptr<graphics::material::Material> getMaterial() const;
                void setMaterial(std::shared_ptr<graphics::material::Material> material);

                glm::vec3 objectColor = glm::vec3(1.0f,0.0f,0.0f);
            private:

            private:
                std::shared_ptr<graphics::mesh::Mesh> _mesh;
                std::shared_ptr<graphics::material::Material> _material;
        };
    } // namespace scene

} // namespace graphics

#include "SceneObject.hpp"
#include "graphics/mesh/Mesh.hpp"
#include "graphics/material/Material.hpp"
namespace graphics
{
    namespace scene
    {
        SceneObject::SceneObject(glm::vec3 objColor) : objectColor{objColor}
        {
        }

        std::shared_ptr<graphics::mesh::Mesh> SceneObject::getMesh() const
        {
            return _mesh;
        }

        void SceneObject::setMesh(std::shared_ptr<graphics::mesh::Mesh> mesh)
        {
            _mesh = mesh;
        }

        std::shared_ptr<graphics::material::Material> SceneObject::getMaterial() const
        {
            return _material;
        }

        void SceneObject::setMaterial(std::shared_ptr<graphics::material::Material> material)
        {
            _material = material;
        }

    } // namespace scene
} // namespace graphics

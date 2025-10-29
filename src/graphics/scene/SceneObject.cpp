#include "SceneObject.hpp"
#include "graphics/mesh/Mesh.hpp"
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

    } // namespace scene
} // namespace graphics

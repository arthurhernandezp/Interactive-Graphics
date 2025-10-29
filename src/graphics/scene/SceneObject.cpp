#include "SceneObject.hpp"
#include "graphics/mesh/Mesh.hpp"
namespace graphics
{
    namespace scene
    {
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

#pragma once
#include <memory>
#include "graphics/scene/SceneObject.hpp"
#include "graphics/lighting/Light.hpp"
#include "graphics/mesh/Mesh.hpp"
namespace graphics
{
    namespace scene
    {
        class SceneObject;

        class Scene
        {
            public:
                Scene() = default;
                ~Scene();
                void load();
                void swapVisualizationMode();
                void update(float deltaTime);

                const std::vector<std::shared_ptr<scene::SceneObject>>& getSceneObjects();
                const std::vector<std::shared_ptr<lighting::Light>>& getLights() const;
            private:
                void loadMeshes();
                void loadObjects();
            private:
                std::vector<std::shared_ptr<scene::SceneObject>> _objects;
                std::vector<std::shared_ptr<lighting::Light>> _lights;
                std::vector<std::shared_ptr<graphics::mesh::Mesh>> _meshes;
        };
    } // namespace scene

} // namespace graphics

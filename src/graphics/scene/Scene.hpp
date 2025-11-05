#pragma once
#include <memory>
#include <map>
#include "graphics/scene/SceneObject.hpp"
#include "graphics/lighting/Light.hpp"
#include "graphics/mesh/Mesh.hpp"
#include "graphics/material/Material.hpp"

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
                void loadMaterials();
                void loadObjects();
            private:
                std::vector<std::shared_ptr<scene::SceneObject>> _objects;
                std::vector<std::shared_ptr<lighting::Light>> _lights;
                std::map<std::string,std::shared_ptr<graphics::mesh::Mesh>> _meshes;
                std::map<std::string,std::shared_ptr<graphics::material::Material>> _materials;
        };
    } // namespace scene

} // namespace graphics

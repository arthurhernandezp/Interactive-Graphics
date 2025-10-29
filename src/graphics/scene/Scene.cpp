#include "Scene.hpp"
#include <iostream>

namespace graphics
{
    namespace scene
    {
        Scene::~Scene()
        {
        }

        void Scene::load()
        {                
            std::shared_ptr<graphics::mesh::Mesh> mesh;
            std::shared_ptr<graphics::scene::SceneObject> bule;
            mesh = std::make_shared<graphics::mesh::Mesh>("resources/teapot.obj");

            bule = std::make_shared<graphics::scene::SceneObject>();
            bule->setMesh(mesh);
            bule->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule->transform.setRotationAngleDeegres(-90.0f);
            bule->transform.setPosition(glm::vec3(0.0, 0.0, -10.0));

            std::shared_ptr<graphics::lighting::Light> lightCube;
            lightCube = std::make_shared<lighting::Light>();
            lightCube->transform.setRotation(glm::vec3(0.0f, 1.0f, 1.0f));
            lightCube->transform.setRotationAngleDeegres(60.0f);

            _objects.emplace_back(bule);
            _lights.emplace_back(lightCube);
        }

        void Scene::swapVisualizationMode()
        {
            for(auto & sceneObject : _objects)
                sceneObject->getMesh()->swapRenderMode();
        }

        void Scene::update(float deltaTime)
        {
            // Animação de rotação da luz
            auto & light = _lights.at(0);
            light->transform.setRotationAngleDeegres(deltaTime* 60.0f);
            light->lightSource = light->transform.getModelMatrix() * glm::vec4(light->lightSource, 1.0f);

        }

        const std::vector<std::shared_ptr<scene::SceneObject>> &Scene::getSceneObjects()
        {
            return _objects;
        }

        const std::vector<std::shared_ptr<lighting::Light>> &Scene::getLights() const
        {
            return _lights;
        }

    } // namespace scene
    
} // namespace graphcis

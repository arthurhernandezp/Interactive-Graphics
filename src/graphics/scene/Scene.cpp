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

            bule = std::make_shared<graphics::scene::SceneObject>(glm::vec3{1.0f,0.0f,0.0f});
            bule->setMesh(mesh);
            bule->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule->transform.setRotationAngleDeegres(-90.0f);
            bule->transform.setPosition(glm::vec3(0.0, 0.0, -10.0));
            _objects.emplace_back(bule);


            std::shared_ptr<graphics::scene::SceneObject> bule2;

            bule2 = std::make_shared<graphics::scene::SceneObject>(glm::vec3{0.0f,1.0f,0.0f});
            bule2->setMesh(mesh);
            bule2->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule2->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule2->transform.setRotationAngleDeegres(-90.0f);
            bule2->transform.setPosition(glm::vec3(0.0, 0.0, 10.0));
            _objects.emplace_back(bule2);


            std::shared_ptr<graphics::scene::SceneObject> bule3;

            bule3 = std::make_shared<graphics::scene::SceneObject>(glm::vec3{0.0f,0.0f,1.0f});
            bule3->setMesh(mesh);
            bule3->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule3->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule3->transform.setRotationAngleDeegres(-90.0f);
            bule3->transform.setPosition(glm::vec3(0.0, -80.0, 10.0));
            _objects.emplace_back(bule3);

            std::shared_ptr<graphics::scene::SceneObject> bule4;

            bule4 = std::make_shared<graphics::scene::SceneObject>(glm::vec3{1.0f,0.0f,1.0f});
            bule4->setMesh(mesh);
            bule4->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule4->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule4->transform.setRotationAngleDeegres(-90.0f);
            bule4->transform.setPosition(glm::vec3(0.0, -80.0, -10.0));
            _objects.emplace_back(bule4);

            std::shared_ptr<graphics::scene::SceneObject> bule5;

            bule5 = std::make_shared<graphics::scene::SceneObject>(glm::vec3{1.0f,1.0f,0.0f});
            bule5->setMesh(mesh);
            bule5->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule5->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule5->transform.setRotationAngleDeegres(-90.0f);
            bule5->transform.setPosition(glm::vec3(40.0, -40.0, -10.0));
            _objects.emplace_back(bule5);

            std::shared_ptr<graphics::scene::SceneObject> bule6;

            bule6 = std::make_shared<graphics::scene::SceneObject>(glm::vec3{0.0f,1.0f,1.0f});
            bule6->setMesh(mesh);
            bule6->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule6->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule6->transform.setRotationAngleDeegres(-90.0f);
            bule6->transform.setPosition(glm::vec3(40.0, -40.0, 10.0));
            _objects.emplace_back(bule6);

            std::shared_ptr<graphics::lighting::Light> lightCube;
            lightCube = std::make_shared<lighting::Light>();
            lightCube->transform.setRotation(glm::vec3(0.0f, 1.0f, 1.0f));
            lightCube->transform.setRotationAngleDeegres(60.0f);

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

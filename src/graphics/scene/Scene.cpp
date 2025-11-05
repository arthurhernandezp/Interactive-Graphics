#include "Scene.hpp"
#include <iostream>
#include "graphics/mesh/MeshLoader.hpp"
namespace graphics
{
    namespace scene
    {
        Scene::~Scene()
        {
        }

        void Scene::load()
        {
            loadMeshes();
            loadMaterials();
            loadObjects();
        }

        void Scene::swapVisualizationMode()
        {
            for(auto & mesh : _meshes)
            {
                mesh.second->swapRenderMode();
            }
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

        void Scene::loadMeshes()
        {
            std::shared_ptr<graphics::mesh::Mesh> mesh = graphics::mesh::MeshLoader::loadObj("resources/teapot.obj"); 
            _meshes.emplace("bule",std::move(mesh));
        }

        void Scene::loadMaterials()
        {
            _materials.emplace("brick",std::make_shared<graphics::material::Material>("resources/brick.png"));
            _materials.emplace("brick-especular",std::make_shared<graphics::material::Material>("resources/brick-specular.png"));
        }

        void Scene::loadObjects()
        {
            std::shared_ptr<graphics::scene::SceneObject> bule;

            bule = std::make_shared<graphics::scene::SceneObject>(glm::vec3{1.0f,0.0f,0.0f});
            bule->setMesh(_meshes["bule"]);
            bule->setMaterial(_materials["brick"]);
            bule->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule->transform.setRotationAngleDeegres(-90.0f);
            bule->transform.setPosition(glm::vec3(0.0, 0.0, -10.0));
            _objects.emplace_back(bule);

            std::shared_ptr<graphics::scene::SceneObject> bule2;

            bule2 = std::make_shared<graphics::scene::SceneObject>(glm::vec3{0.0f,1.0f,0.0f});
            bule2->setMesh(_meshes["bule"]);
            bule2->setMaterial(_materials["brick"]);
            bule2->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule2->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule2->transform.setRotationAngleDeegres(-90.0f);
            bule2->transform.setPosition(glm::vec3(0.0, 0.0, 10.0));
            _objects.emplace_back(bule2);

            std::shared_ptr<graphics::scene::SceneObject> bule3;

            bule3 = std::make_shared<graphics::scene::SceneObject>(glm::vec3{0.0f,0.0f,1.0f});
            bule3->setMesh(_meshes["bule"]);
            bule3->setMaterial(_materials["brick"]);
            bule3->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule3->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule3->transform.setRotationAngleDeegres(-90.0f);
            bule3->transform.setPosition(glm::vec3(0.0, -80.0, 10.0));
            _objects.emplace_back(bule3);

            std::shared_ptr<graphics::scene::SceneObject> bule4;

            bule4 = std::make_shared<graphics::scene::SceneObject>(glm::vec3{1.0f,0.0f,1.0f});
            bule4->setMesh(_meshes["bule"]);
            bule4->setMaterial(_materials["brick"]);
            bule4->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule4->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule4->transform.setRotationAngleDeegres(-90.0f);
            bule4->transform.setPosition(glm::vec3(0.0, -80.0, -10.0));
            _objects.emplace_back(bule4);

            std::shared_ptr<graphics::scene::SceneObject> bule5;

            bule5 = std::make_shared<graphics::scene::SceneObject>(glm::vec3{1.0f,1.0f,0.0f});
            bule5->setMesh(_meshes["bule"]);
            bule5->setMaterial(_materials["brick"]);
            bule5->transform.setScale(glm::vec3(0.5, 0.5, 0.5));
            bule5->transform.setRotation(glm::vec3(1.0, 0.0, 0.0));
            bule5->transform.setRotationAngleDeegres(-90.0f);
            bule5->transform.setPosition(glm::vec3(40.0, -40.0, -10.0));
            _objects.emplace_back(bule5);

            std::shared_ptr<graphics::scene::SceneObject> bule6;

            bule6 = std::make_shared<graphics::scene::SceneObject>(glm::vec3{0.0f,1.0f,1.0f});
            bule6->setMesh(_meshes["bule"]);
            bule6->setMaterial(_materials["brick"]);
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
    } // namespace scene

} // namespace graphcis

#include "Renderer.hpp"

#include "graphics/renderer/ShaderProgram.hpp"  //mesh program and light program

#include "graphics/scene/Scene.hpp"

#include "graphics/scene/SceneObject.hpp"
#include "graphics/lighting/Light.hpp"
#include "graphics/mesh/Mesh.hpp"
#include "graphics/Material/Material.hpp"

#include "core/Camera.hpp"

#include <iostream>

namespace graphics
{
    namespace renderer
    {
        Renderer::~Renderer()
        {
        }

        void Renderer::init()
        {
            std::cout << "glfw version: " << glfwGetVersionString() << '\n';
            _OpenGLContext = std::make_unique<graphics::renderer::OpenGLContext>(3,3,GLFW_OPENGL_CORE_PROFILE);

            createShadersProgram();

            isRunning = true;
        }

        void Renderer::update(scene::Scene &scene, std::shared_ptr<core::Camera> camera)
        {
            // Variavel de seguranca para rodar o update somente se o init tiver sido chamado antes
            if(!isRunning)
            {
                throw std::runtime_error("Init Render function was not called");
                return; 
            }

            glm::mat4 view, projection;
            camera->Matrix(45.0f, 0.1f, 100.0f, view, projection);

            // Verifica se existe iluminação para desenhar algo
            if (scene.getLights().empty()) return; 
            auto light = scene.getLights()[0]; 

            // Ativar o shader para malhas
            _meshProgram->use();

            // Enviar uniforms da LUZ
            _meshProgram->sendUniform("ulightPos", light->lightSource);
            _meshProgram->sendUniform("uLightIntensity", light->intensity);
            _meshProgram->sendUniform("uAmbientStrength", light->ambientIntensity);
            _meshProgram->sendUniform("uSpecularStrength", light->specularStrength);
            _meshProgram->sendUniform("uLightColor", light->lightColor);

            // Enviar o 'modelViewLight'
            glm::mat4 modelViewLight = view * glm::mat4(1.0f); // view * identidade = view
            _meshProgram->sendUniform("modelViewLight", modelViewLight);

            for (const auto& sceneObject : scene.getSceneObjects())
            {
                glm::mat4 model =  sceneObject->transform.getModelMatrix();

                glm::mat4 mvp = projection * view * model;
                _meshProgram->sendUniform("mvp",mvp);

                auto modelView = view * model;
                _meshProgram->sendUniform("modelViewFrag", modelView);

                glm::mat3 normalMatrix = glm::inverse((glm::transpose(view * model)));
                _meshProgram->sendUniform("normalMatrix", normalMatrix);

                _meshProgram->sendUniform("uObjectColor", sceneObject->objectColor);

                auto meshMaterial = sceneObject->getMaterial();
                meshMaterial->applyTo(_meshProgram); 
                    
                sceneObject->getMesh()->draw();
            }

            // Light Cube

            _lightProgram->use();

            glm::mat4 model =  light->transform.getModelMatrix();
            light->lightPosition *= model;
            glm::mat4 mvp = projection * view * light->lightPosition;
            _lightProgram->sendUniform("mvp",mvp);
            _lightProgram->sendUniform("uLightColor",light->lightColor);

            light->draw();
        }

        void Renderer::clear()
        {
            glClearColor(_backgrounColor.r, _backgrounColor.g, _backgrounColor.b, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
        }

        const std::vector<std::shared_ptr<ShaderProgram>>& Renderer::getShaders() const
        {
            return _shaders;
        }

        void Renderer::createShadersProgram()
        {   
            _meshProgram = std::make_shared<graphics::renderer::ShaderProgram>("shaders/shader.vert","shaders/shader.frag");
            _shaders.push_back(_meshProgram);
            _lightProgram = std::make_shared<graphics::renderer::ShaderProgram>("shaders/light.vert","shaders/light.frag");
            _shaders.push_back(_lightProgram);
        }

    } // namespace renderer
    
} // namespace graphics

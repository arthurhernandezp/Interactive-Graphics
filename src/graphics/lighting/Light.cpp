#include "Light.hpp"
#include <iostream>

namespace graphics
{
    namespace lighting
    {
        Light::Light()
        {
            std::cout << "Light constructor called" << '\n';

            using graphics::renderer::VertexArrayObject;        //VAO
            using graphics::renderer::VertexBufferObject;       //VBO
            using graphics::renderer::ElementBufferObject;       //EBO

            createCubeLight();
            createCubeIndices();

            _vao = std::make_shared<VertexArrayObject>();
            _vao->bindBuffer();

            // Cria o buffer com os vértices que estarao no layout location 0 do vertex shader (VBO)
            _vboPos = std::make_shared<VertexBufferObject>();
            _vboPos->setLayout(0);
            _vboPos->receiveData(cubeVertices,GL_STATIC_DRAW);
            _vao->LinkVBO(*_vboPos);

            _ebo =  std::make_shared<ElementBufferObject>(cubeIndices.data(),cubeIndices.size() * sizeof(cubeIndices.front()));

            std::cout << "Numero de vertices do light cube: " << cubeVertices.size()/3 << std:: endl;

            _vao->unbindBuffer();
            _vboPos->unbindBuffer();
            _ebo->unbindBuffer();
        }

        Light::~Light()
        {
            std::cout << "Light destructor called" << '\n';
        }

        void Light::draw() const
        {
            _vao->bindBuffer();
            glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
            _vao->unbindBuffer();
        }

        void Light::createCubeLight()
        {
            float hs = cubeSize / 2.0f; // half size

            glm::vec3 center = lightSource;

            cubeVertices.clear();
            // Define os 8 vértices do cubo
            std::vector<glm::vec3> positions = {
                center + glm::vec3(-hs, -hs, -hs), // 0
                center + glm::vec3( hs, -hs, -hs), // 1
                center + glm::vec3( hs,  hs, -hs), // 2
                center + glm::vec3(-hs,  hs, -hs), // 3
                center + glm::vec3(-hs, -hs,  hs), // 4
                center + glm::vec3( hs, -hs,  hs), // 5
                center + glm::vec3( hs,  hs,  hs), // 6
                center + glm::vec3(-hs,  hs,  hs)  // 7
            };

            // Insere cada vértice como float (x, y, z)
            for (const auto& pos : positions)
            {
                cubeVertices.push_back(pos.x);
                cubeVertices.push_back(pos.y);
                cubeVertices.push_back(pos.z);
            }
        }

    void Light::createCubeIndices()
    {
        cubeIndices.clear();

        // Face traseira (z-)
        cubeIndices.push_back(0); cubeIndices.push_back(1); cubeIndices.push_back(2);
        cubeIndices.push_back(2); cubeIndices.push_back(3); cubeIndices.push_back(0);

        // Face dianteira (z+)
        cubeIndices.push_back(4); cubeIndices.push_back(5); cubeIndices.push_back(6);
        cubeIndices.push_back(6); cubeIndices.push_back(7); cubeIndices.push_back(4);

        // Face esquerda (x-)
        cubeIndices.push_back(0); cubeIndices.push_back(3); cubeIndices.push_back(7);
        cubeIndices.push_back(7); cubeIndices.push_back(4); cubeIndices.push_back(0);

        // Face direita (x+)
        cubeIndices.push_back(1); cubeIndices.push_back(5); cubeIndices.push_back(6);
        cubeIndices.push_back(6); cubeIndices.push_back(2); cubeIndices.push_back(1);

        // Face inferior (y-)
        cubeIndices.push_back(0); cubeIndices.push_back(1); cubeIndices.push_back(5);
        cubeIndices.push_back(5); cubeIndices.push_back(4); cubeIndices.push_back(0);

        // Face superior (y+)
        cubeIndices.push_back(3); cubeIndices.push_back(2); cubeIndices.push_back(6);
        cubeIndices.push_back(6); cubeIndices.push_back(7); cubeIndices.push_back(3);
    }
    } // namespace lighting
} // namespace graphics

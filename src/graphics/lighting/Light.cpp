#include "Light.hpp"
#include <iostream>

namespace graphics
{
    namespace lighting
    {
        Light::Light()
        {
            // //                                      0.0f,0.0f,0.0f,
            //                                         0.0f, 10.0f, 10.0f,
            //                                         0.0f, 10.0f, 10.0f
            for( float i = -10.0f; i <= 10.0f; i+= 0.2f)
            {
                _directionalLightVertex.push_back(i);
                _directionalLightVertex.push_back(0.0f);
                _directionalLightVertex.push_back(0.0f);

                _directionalLightVertex.push_back(i);
                _directionalLightVertex.push_back(10.0f);
                _directionalLightVertex.push_back(10.0f);

                _directionalLightVertex.push_back(i);
                _directionalLightVertex.push_back(10.0f);
                _directionalLightVertex.push_back(10.0f);
            }

            std::cout << "Light constructor called" << '\n';
            using graphics::renderer::VertexArrayObject;        //VAO
            using graphics::renderer::VertexBufferObject;       //VBO

            _vao = std::make_shared<VertexArrayObject>();
            _vao->bindBuffer();

            // Cria o buffer com os vértices que estarao no layout location 0 do vertex shader (VBO)
            _vboPos = std::make_shared<VertexBufferObject>();
            _vboPos->setLayout(0);
            _vboPos->receiveData(_directionalLightVertex,GL_STATIC_DRAW);
            _vao->LinkVBO(*_vboPos);

            std::cout << "Numero de vertices: " << _directionalLightVertex.size()/3 << std:: endl;

            _vao->unbindBuffer();
            _vboPos->unbindBuffer();
        }

        Light::~Light()
        {
            std::cout << "Light destructor called" << '\n';
        }

        void Light::draw() const
        {
            _vao->bindBuffer();
            glPointSize(10.5f);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawArrays(GL_TRIANGLES, 0,_directionalLightVertex.size());
            _vao->unbindBuffer();
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
        glm::vec3& Light::getLightSource()
        {
            return _lightSource;
        }
    } // namespace lighting
} // namespace graphics

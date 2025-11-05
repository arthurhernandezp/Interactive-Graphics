#include "Triangle.hpp"
#include <iostream>
namespace graphics
{
    namespace geometry
    {
        Triangle::Triangle(std::vector<float> v,std::vector<float> vn,std::vector<float>vt)
        {

            using graphics::renderer::VertexArrayObject;
            using graphics::renderer::VertexBufferObject;

            _vertices = v;
            _texCoords = vt;
            if(!vn.empty())
            {
                for(size_t i = 0; i < _vertices.size()/ 3; ++i)
                {
                    for(auto & n: vn)
                    {
                        _normal.push_back(n);
                    }
                }
            }
            _vao = std::make_shared<VertexArrayObject>();
            _vao->bindBuffer();

            // Cria o buffer com os vértices que estarao no layout location 0 do vertex shader (VBO)
            _vbo = std::make_shared<VertexBufferObject>();
            _vbo->setLayout(0);
            _vbo->receiveData(_vertices,GL_STATIC_DRAW);
            _vao->LinkVBO(*(_vbo));

            // Cria o buffer com os vértices que estarao no layout location 1 do vertex shader (VBO)
            _vboNormal = std::make_shared<VertexBufferObject>();
            _vboNormal->setLayout(1);
            _vboNormal->receiveData(_normal,GL_STATIC_DRAW);
            _vao->LinkVBO(*(_vboNormal));

            // Cria o buffer com os vértices que estarao no layout location 2 do vertex shader (VBO)
            _vboTexCoords = std::make_shared<VertexBufferObject>();
            _vboTexCoords->setLayout(2);
            _vboTexCoords->receiveData(_texCoords,GL_STATIC_DRAW);
            _vao->LinkVBO(*(_vboTexCoords),2);

            std::cout << "_vertices.size() : " << _vertices.size() << '\n';
            std::cout << "_normal.size() : " << _normal.size() << '\n';
            _vao->unbindBuffer();
            _vbo->unbindBuffer();
        }

        Triangle::~Triangle()
        {
            std::cout << "Destructor of Triangle called" << '\n';
        }

        void Triangle::draw()
        {
            _vao->bindBuffer();
            glDrawArrays(GL_TRIANGLES,0, _vertices.size());
            _vao->unbindBuffer();
        }

    } // namespace geometry
    
} // namespace graphics

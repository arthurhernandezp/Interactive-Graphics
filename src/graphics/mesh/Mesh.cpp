#include "Mesh.hpp"
#include <iostream>

namespace graphics
{
    namespace mesh
    {
        Mesh::Mesh(const std::vector<float>& vertices,
                   const std::vector<float>& normals,
                   const std::vector<float>& texCoords,
                   const std::vector<int>& indices)
        {

            _vertices = vertices;
            _normal = normals;
            _texCoords = texCoords;
            _indices = indices;

            using graphics::renderer::VertexArrayObject;        //VAO
            using graphics::renderer::VertexBufferObject;       //VBO
            using graphics::renderer::ElementBufferObject;      //EBO

            _vao = std::make_shared<VertexArrayObject>();
            _vao->bindBuffer();

            // Cria o buffer com os vértices que estarao no layout location 0 do vertex shader (VBO)
            _vboPos = std::make_shared<VertexBufferObject>();
            _vboPos->setLayout(0);
            _vboPos->receiveData(_vertices,GL_STATIC_DRAW);
            _vao->LinkVBO(*_vboPos);

            // Cria o buffer com as normal que estarao no layout location 1 do vertex shader (VBO)
            _vboNormal = std::make_shared<VertexBufferObject>();
            _vboNormal->receiveData(_normal,GL_STATIC_DRAW);
            _vboNormal->setLayout(1);
            _vao->LinkVBO(*_vboNormal);

            // Cria o buffer com as normal que estarao no layout location 2 do vertex shader (VBO)
            _vboTexCoords = std::make_shared<VertexBufferObject>();
            _vboTexCoords->receiveData(_texCoords,GL_STATIC_DRAW);
            _vboTexCoords->setLayout(2);
            _vao->LinkVBO(*_vboTexCoords,2);

            _ebo =  std::make_shared<ElementBufferObject>(_indices.data(),_indices.size() * sizeof(_indices.front()));

            // Unbind all to prevent accidentally modifying them
            _vao->unbindBuffer();
            _vboPos->unbindBuffer();
            _vboNormal->unbindBuffer();
            _ebo->unbindBuffer();

            std::cout << "Numero de vertices: " << _vertices.size()/3 << std:: endl;
            std::cout << "Numero de Normal: " << _normal.size()/3 << '\n';
            std::cout << "Numero de TextureCoords: " << _texCoords.size()/2 << '\n';
            std::cout << "Triangular mesh size: " << _indices.size() << '\n';
        }

        Mesh::~Mesh()
        {
            std::cout << "Destroying mesh" << '\n';
        }

        void Mesh::draw() const
        {
            _vao->bindBuffer();
            glDrawElements(_renderMode, _indices.size(), GL_UNSIGNED_INT, 0);
            _vao->unbindBuffer();
        }

        void Mesh::swapRenderMode()
        {
            static int swapCounter = 0;

            switch (swapCounter)
            {
                case 0: _renderMode = GL_LINES;     break;
                case 1: _renderMode = GL_POINTS;    break;
                case 2: _renderMode = GL_TRIANGLES; break;
            }
            
            swapCounter++;
            if(swapCounter >= 3)
            {
                swapCounter = 0;
            }
        }

    } // namespace mesh
} // namespace graphics

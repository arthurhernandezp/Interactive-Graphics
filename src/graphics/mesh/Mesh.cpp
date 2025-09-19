#include "Mesh.hpp"
#include <iostream>

namespace graphics
{
    namespace mesh
    {
        Mesh::Mesh(const std::string &objFilePath) : _objFilePath{objFilePath}
        {
            using graphics::renderer::VertexArrayObject;        //VAO
            using graphics::renderer::VertexBufferObject;       //VBO
            using graphics::renderer::ElementBufferObject;      //EBO

            loadObj();
            _vao = std::make_shared<VertexArrayObject>();
            _vao->bindBuffer();

            // Cria o buffer com os vértices que estarao no layout location 0 do vertex shader (VBO)
            _vboPos = std::make_shared<VertexBufferObject>();
            _vboPos->setLayout(0);
            _vboPos->receiveData(_vertices,GL_STATIC_DRAW);
            _vao->LinkVBO(*_vboPos);

            // Cria o buffer com as normal que estarao no layout location 0 do vertex shader (VBO)
            _vboNormal = std::make_shared<VertexBufferObject>();
            _vboNormal->receiveData(_normal,GL_STATIC_DRAW);
            _vboNormal->setLayout(1);
            _vao->LinkVBO(*_vboNormal);

            _ebo =  std::make_shared<ElementBufferObject>(_indices.data(),_indices.size() * sizeof(_indices.front()));

            // Unbind all to prevent accidentally modifying them
            _vao->unbindBuffer();
            _vboPos->unbindBuffer();
            _vboNormal->unbindBuffer();
            _ebo->unbindBuffer();

            std::cout << "Numero de vertices: " << _vertices.size()/3 << std:: endl;
            std::cout << "Numero de Normal: " << _normal.size()/3 << '\n';
            std::cout << "Triangular mesh size: " << _indices.size() << '\n';
        }

        Mesh::~Mesh()
        {
            std::cout << "Destroying mesh" << '\n';
        }

        void Mesh::draw() const
        {
            auto drawMesh   = [&] { glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0); };
            auto drawVertex = [&] { glDrawArrays(GL_POINTS, 0,_vertices.size());  };

            _vao->bindBuffer();
            (_renderMode == MeshRenderMode::FULLMESH) ?  drawMesh() : drawVertex();
            _vao->unbindBuffer();
        }

        void Mesh::swapRenderMode()
        {
            (_renderMode == MeshRenderMode::FULLMESH) ?
            _renderMode = MeshRenderMode::VERTICES_ONLY :
            _renderMode = MeshRenderMode::FULLMESH;
        }

        void Mesh::loadObj()
        {
            std::ifstream file(_objFilePath);
            if (!file.is_open()) 
            {
                std::cout << "Nao foi possivel abrir o arquivo : " << _objFilePath << std::endl;
                return;
            }

            _vertices.clear();
            _indices.clear(); 
            _normal.clear();

            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string type;
                iss >> type;

                if (type == "v")
                {
                    float x, y, z;
                    if (iss >> x >> y >> z) {
                        _vertices.push_back(x);
                        _vertices.push_back(y);
                        _vertices.push_back(z);
                    }
                }

                else if (type == "vn")
                {
                    float xn, yn, zn;
                    if(iss >> xn >> yn >> zn)
                    _normal.push_back(xn);
                    _normal.push_back(yn);
                    _normal.push_back(zn);
                }

                else if (type == "f") {
                    std::vector<int> faceIndices;
                    std::string vertexData;
                    while (iss >> vertexData) {
                        
                        size_t slashPos = vertexData.find('/');
                        std::string vertexIndexStr = vertexData.substr(0, slashPos);
                        try {
                            int vertexIndex = std::stoi(vertexIndexStr) - 1; // OBJ usa índices base 1
                            faceIndices.push_back(vertexIndex);
                        } catch (const std::exception& e) {
                            std::cout << "Error parsing face index: " << vertexData << std::endl;
                        }
                    }

                    // Triangulação
                    if (faceIndices.size() >= 3) 
                    {
                        for (size_t i = 1; i + 1 < faceIndices.size(); ++i) 
                        {
                            _indices.push_back(faceIndices[0]);
                            _indices.push_back(faceIndices[i]);
                            _indices.push_back(faceIndices[i + 1]);
                        }
                    }
                }
            }

            file.close();
            std::cout << "Loaded " << _vertices.size() / 3 << " vertices and "
                    << _indices.size() / 3 << " triangles from " << _objFilePath << std::endl;
        }
    } // namespace mesh
} // namespace graphics


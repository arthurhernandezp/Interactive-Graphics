#include "MeshLoader.hpp"

#include <iostream>
#include <fstream>   // Para std::ifstream
#include <sstream>   // Para std::istringstream
#include <vector>
#include <map>       
#include <glm/glm.hpp> 

namespace graphics
{
    namespace mesh
    {
        std::shared_ptr<mesh::Mesh> MeshLoader::loadObj(const std::string& objFilePath)
        {
            std::ifstream file(objFilePath);
            if (!file.is_open())
            {
                std::cout << "Nao foi possivel abrir o arquivo : " << objFilePath << std::endl;
                // Retorna um ponteiro nulo se falhar
                return nullptr; 
            }

            // vector temporario para armazenar os dados brutos lidos do .obj
            std::vector<glm::vec3> temp_positions;
            std::vector<glm::vec3> temp_normals;
            std::vector<glm::vec2> temp_texCoords;

            // vector final que serão enviados para o construtor da Mesh
            std::vector<float> final_vertices;
            std::vector<float> final_normals;
            std::vector<float> final_texCoords;
            std::vector<int> final_indices;

            // Cache para reusar vertices
            // A chave e a string "v/vt/vn", o valor é o novo índice final
            std::map<std::string, int> vertexCache;

            std::string line;
            while (std::getline(file, line))
            {
                std::istringstream iss(line);
                std::string type;
                iss >> type;

                // vertices
                if (type == "v")
                {
                    float x, y, z;
                    if (iss >> x >> y >> z) {
                        temp_positions.push_back({x, y, z});
                    }
                }
                // normals
                else if (type == "vn")
                {
                    float xn, yn, zn;
                    if (iss >> xn >> yn >> zn) {
                        temp_normals.push_back({xn, yn, zn});
                    }
                }
                // tex coords
                else if (type == "vt")
                {
                    float xt, yt;
                    if (iss >> xt >> yt) {
                        // Inverte o Y da textura (OpenGL vs. formato de imagem)
                        temp_texCoords.push_back({xt, 1.0f - yt});
                    }
                }

                //Faces usadas para fazer a triangular mesh
                else if (type == "f")
                {
                    std::vector<unsigned int> faceIndices; // Índices para esta face
                    std::string vertexData;

                    // Loop para cada "v/vt/vn" na linha da face
                    while (iss >> vertexData)
                    {
                        // Verifica se este vértice (combinação v/vt/vn) já foi criado
                        if (vertexCache.find(vertexData) != vertexCache.end())
                        {
                            // --- VÉRTICE EXISTENTE ---
                            // Apenas pegue o índice dele e adicione à face
                            faceIndices.push_back(vertexCache[vertexData]);
                        }
                        else
                        {
                            // --- VÉRTICE NOVO ---
                            // Precisamos criá-lo e adicioná-lo às nossas 3 listas
                            std::istringstream v_iss(vertexData);
                            std::string indexStr;
                            int posIdx, texIdx, normIdx;

                            // Parse v/vt/vn (ex: "1/1/1")
                            try 
                            {
                                std::getline(v_iss, indexStr, '/');
                                posIdx = std::stoi(indexStr) - 1; 

                                std::getline(v_iss, indexStr, '/');
                                texIdx = std::stoi(indexStr) - 1;

                                std::getline(v_iss, indexStr, '/');
                                normIdx = std::stoi(indexStr) - 1;
                            } 
                            catch (const std::exception& e) 
                            {
                                std::cerr << "Erro ao fazer parse da face: " << vertexData << " em " << objFilePath << std::endl;
                                continue; // Pula este vértice
                            }

                            // Pegue os dados das listas temporárias
                            glm::vec3 pos  = temp_positions[posIdx];
                            glm::vec2 tex  = temp_texCoords[texIdx];
                            glm::vec3 norm = temp_normals[normIdx];

                            // Adicione os dados ao final das listas de VBO
                            final_vertices.push_back(pos.x);
                            final_vertices.push_back(pos.y);
                            final_vertices.push_back(pos.z);

                            final_normals.push_back(norm.x);
                            final_normals.push_back(norm.y);
                            final_normals.push_back(norm.z);

                            final_texCoords.push_back(tex.x);
                            final_texCoords.push_back(tex.y);

                            // Salve o novo índice no cache
                            unsigned int newIndex = (final_vertices.size() / 3) - 1;
                            vertexCache[vertexData] = newIndex;

                            // Adicione o novo índice à face
                            faceIndices.push_back(newIndex);
                        }
                    }

                    // Triangulação da malha
                    if (faceIndices.size() >= 3)
                    {
                        for (size_t i = 1; i + 1 < faceIndices.size(); ++i)
                        {
                            final_indices.push_back(faceIndices[0]);
                            final_indices.push_back(faceIndices[i]);
                            final_indices.push_back(faceIndices[i + 1]);
                        }
                    }
                }
            }

            file.close();
            
            std::cout << "MeshLoader: Carregou " << (final_vertices.size() / 3) << " vertices e "
                      << (final_indices.size() / 3) << " triangulos de " << objFilePath << std::endl;
            std::cout << "Numero de normals: " << temp_normals.size()/3 << '\n';
            std::cout << "Numero de texcoords: " << temp_texCoords.size()/2 << '\n';

            // Cria um novo Mesh passando os vetores finais
            return std::make_shared<mesh::Mesh>(
                final_vertices,
                final_normals,
                final_texCoords,
                final_indices
            );
        }

    } // namespace mesh
} // namespace graphics
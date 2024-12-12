#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "VertexData.h"

class Loader {
public:
    void LoadObjModel(std::string filename, std::vector<VertexData>& m_vertices, std::vector<int>& m_indices) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return;
        }

        std::vector<std::vector<float>> vertices;
        std::vector<std::vector<float>> texCoords;
        std::vector<std::vector<float>> normals;

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            if (!(iss >> prefix)) { continue; } // ignore empty lines

            if (prefix == "v") {
                std::vector<float> vertex(3);
                for (int i = 0; i < 3; ++i) {
                    iss >> vertex[i];
                }
                vertices.push_back(vertex);
            }
            else if (prefix == "vt") {
                std::vector<float> texCoord(2);
                for (int i = 0; i < 2; ++i) {
                    iss >> texCoord[i];
                }
                texCoords.push_back(texCoord);
            }
            else if (prefix == "vn") {
                std::vector<float> normal(3);
                for (int i = 0; i < 3; ++i) {
                    iss >> normal[i];
                }
                normals.push_back(normal);
            }
            else if (prefix == "f") {
                std::string vertexData[3];
                for (int i = 0; i < 3; ++i) {
                    iss >> vertexData[i];
                    int vertexIndex, texCoordIndex, normalIndex;
                    sscanf_s(vertexData[i].c_str(), "%d/%d/%d", &vertexIndex, &texCoordIndex, &normalIndex);
                    vertexIndex--;
                    texCoordIndex--;
                    normalIndex--;

                    // Создаем VertexData для m_vertices
                    VertexData vd;
                    vd.position[0] = vertices[vertexIndex][0];
                    vd.position[1] = vertices[vertexIndex][1];
                    vd.position[2] = vertices[vertexIndex][2];

                    if (texCoordIndex >= 0) {
                        vd.color[0] = texCoords[texCoordIndex][0];
                        vd.color[1] = texCoords[texCoordIndex][1];
                    }
                    else {
                        vd.color[0] = 0.0f; // Значения по умолчанию
                        vd.color[1] = 0.0f;
                    }

                    if (normalIndex >= 0) {
                        vd.normal[0] = normals[normalIndex][0];
                        vd.normal[1] = normals[normalIndex][1];
                        vd.normal[2] = normals[normalIndex][2];
                    }
                    else {
                        vd.normal[0] = 0.0f; // Значения по умолчанию
                        vd.normal[1] = 0.0f;
                        vd.normal[2] = 1.0f; // Ориентируем нормали по оси Z
                    }

                    m_vertices.push_back(vd);
                    m_indices.push_back(m_vertices.size() - 1); // Индекс текущей вершины
                }
            }
        }

        file.close();
    }
};

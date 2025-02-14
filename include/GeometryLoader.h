#ifndef GEOMETRY_LOADER_H
#define GEOMETRY_LOADER_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Mesh.h"

class GeometryLoader {
public:
    /**
     * Load an OBJ file and create a Mesh object
     * @param filepath Path to the OBJ file
     * @return Unique pointer to a Mesh object
     * @throws std::runtime_error if file cannot be loaded or parsed
     */
    static std::shared_ptr<Mesh> loadFromOBJ(const std::string& filepath) {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        std::ifstream file(filepath);
        if (!file.is_open()) {
            throw std::runtime_error("Could not open OBJ file: " + filepath);
        }

        std::vector<glm::vec3> positions;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec3> colors;

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v") {
                glm::vec3 vertex;
                iss >> vertex.x >> vertex.y >> vertex.z;
                positions.push_back(vertex);
            }
            else if (prefix == "vn") {
                glm::vec3 normal;
                iss >> normal.x >> normal.y >> normal.z;
                normals.push_back(glm::normalize(normal));
            }
            else if (prefix == "f") {
                processface(iss, vertices, indices, positions, normals);
            }
        }

        // Assign a default color if no colors specified
        if (colors.empty()) {
            colors.resize(positions.size(), glm::vec3(0.7f, 0.7f, 0.7f));
        }

        return std::make_shared<Mesh>(vertices, indices);
    }

private:
    static void processface(
        std::istringstream& iss, 
        std::vector<float>& vertices, 
        std::vector<unsigned int>& indices,
        const std::vector<glm::vec3>& positions,
        const std::vector<glm::vec3>& normals
    ) {
        std::string vertexData;
        std::vector<unsigned int> faceIndices;

        while (iss >> vertexData) {
            std::replace(vertexData.begin(), vertexData.end(), '/', ' ');
            std::istringstream vertStream(vertexData);

            unsigned int posIndex, texIndex, normalIndex;
            vertStream >> posIndex >> texIndex >> normalIndex;

            // Adjust for 1-based indexing in OBJ files
            posIndex--;
            normalIndex--;

            // Create a complete vertex with position, normal, and default color
            vertices.push_back(positions[posIndex].x);
            vertices.push_back(positions[posIndex].y);
            vertices.push_back(positions[posIndex].z);

            vertices.push_back(normals[normalIndex].x);
            vertices.push_back(normals[normalIndex].y);
            vertices.push_back(normals[normalIndex].z);

            // Default grey color
            vertices.push_back(0.7f);
            vertices.push_back(0.7f);
            vertices.push_back(0.7f);

            faceIndices.push_back(vertices.size() / 9 - 1);
        }

        // Triangulate non-triangular faces
        if (faceIndices.size() > 3) {
            for (size_t i = 1; i < faceIndices.size() - 1; ++i) {
                indices.push_back(faceIndices[0]);
                indices.push_back(faceIndices[i]);
                indices.push_back(faceIndices[i + 1]);
            }
        }
        else if (faceIndices.size() == 3) {
            indices.push_back(faceIndices[0]);
            indices.push_back(faceIndices[1]);
            indices.push_back(faceIndices[2]);
        }
    }
};

#endif // GEOMETRY_LOADER_H

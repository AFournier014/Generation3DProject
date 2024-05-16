#include "terrain/Chunk.h"
#include "Config.h"
#include "terrain/PerlinNoise.h"
#include <iostream>

#include "terrain/HeightMapGenerator.h"


Chunk::Chunk(const int size, const std::shared_ptr<RenderConfig>& renderConfig)
    : m_size(size), m_renderConfig(renderConfig)
{
}

void Chunk::generate_mesh(HeightMap height_map, Vector3D<float> pos)
{
    std::vector<Vertexf> vertices;
    std::vector<unsigned int> indices;
    auto texture = m_renderConfig->texture;

    Color3<float> color = {1, 1, 1};
    for (int i = 0; i <= m_size; ++i)
    {
        for (int j = 0; j <= m_size; ++j)
        {
            // TODO: fix colors
            if (j % 3 == 0)
                color = {
                    static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX,
                    static_cast<float>(rand()) / RAND_MAX
                };
            float u = static_cast<float>(i) / static_cast<float>(m_size) * 5;
            float v = static_cast<float>(j) / static_cast<float>(m_size) * 5;
            float height = height_map.values[i][j];
            // TODO: remove log
            // std::cout << "Height: " << height << std::endl;
            Vertexf vertex = {
                {pos.x() + i, pos.y() + height, pos.z() - j}, {0, 1, 0}, color,
                {u, v}
            };
            vertices.push_back(vertex);
        }
    }

    for (int i = 0; i < m_size; ++i)
    {
        for (int j = 0; j < m_size; ++j)
        {
            int BottomLeft = i + j * (m_size + 1);
            int BottomRight = BottomLeft + 1;
            int TopLeft = BottomLeft + m_size + 1;
            int TopRight = TopLeft + 1;

            // Bottom triangle
            indices.push_back(BottomLeft);
            indices.push_back(TopLeft);
            indices.push_back(TopRight);

            // Top triangle
            indices.push_back(BottomLeft);
            indices.push_back(TopRight);
            indices.push_back(BottomRight);
        }
    }

    recalculate_normals(vertices, indices);
    m_mesh = std::make_unique<Mesh>(vertices, indices, m_renderConfig);
}

void Chunk::render() const
{
    if (m_mesh)
        m_mesh->render();
}

void Chunk::recalculate_normals(std::vector<Vertexf>& vertices, const std::vector<unsigned int>& indices)
{
    for (int i = 0; i < indices.size(); i += 3)
    {
        Vector3D<float> v0 = vertices[indices[i]].position;
        Vector3D<float> v1 = vertices[indices[i + 1]].position;
        Vector3D<float> v2 = vertices[indices[i + 2]].position;

        Vector3D<float> normal = -(v1 - v0).CrossProduct(v2 - v0).Normalize();

        vertices[indices[i]].normal = normal;
        vertices[indices[i + 1]].normal = normal;
        vertices[indices[i + 2]].normal = normal;
    }
}

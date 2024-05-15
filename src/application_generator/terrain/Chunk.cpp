#include "Config.h"
#include "terrain/Chunk.h"
#include "terrain/PerlinNoise.h"


Chunk::Chunk(const int size, const Vector3D<float>& position) : m_size(size), m_position(position)
{
    generate_mesh(size, position);
}

void Chunk::generate_mesh(int chunkSize, Vector3D<float> pos)
{
    std::vector<Vertexf> vertices;
    std::vector<unsigned int> indices;
    Texture texture(Config::TEXTURES_PATH + "texture.png");


    PerlinNoise pn(static_cast<unsigned int>(time(nullptr)));
    double xOff = 0.0;
    double zOff = 0.0;
    double min = 0;
    double max = GetRand(static_cast<int>(min) + 1, 25);
    double noiseValue = 0.0;
    float modifier = GetRandF(0.01f, 0.08f);

    
    Color3<float> color = {1, 1, 1};
    for (int i = 0; i <= chunkSize; ++i)
    {
        xOff = 0.0;
        for (int j = 0; j <= chunkSize; ++j)
        {
            // TODO: fix colors
            if (j % 3 == 0)
                color = {
                    static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX,
                    static_cast<float>(rand()) / RAND_MAX
                };
            noiseValue = pn.noise(xOff, 0, zOff);
            float height = MapValue(static_cast<float>(min), static_cast<float>(max), static_cast<float>(noiseValue));
            Vertexf vertex = {
                {pos.x() + i, pos.y() + height, pos.z() + j}, {0, 1, 0}, color,
                {0, 0}
            };
            vertices.push_back(vertex);
            
            xOff += modifier;
        }
        zOff += modifier;
    }

    for (int i = 0; i < chunkSize; ++i)
    {
        for (int j = 0; j < chunkSize; ++j)
        {
            int BottomLeft = i + j * (chunkSize + 1);
            int BottomRight = BottomLeft + 1;
            int TopLeft = BottomLeft + chunkSize + 1;
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

    //recalculate_normals(vertices, indices);

    m_mesh = new Mesh(vertices, indices, texture);
}

void Chunk::recalculate_normals(std::vector<Vertexf>& vertices, const std::vector<unsigned int>& indices)
{
    for (int i = 0; i < indices.size(); i += 3)
    {
        Vector3D<float> v0 = vertices[indices[i]].position;
        Vector3D<float> v1 = vertices[indices[i + 1]].position;
        Vector3D<float> v2 = vertices[indices[i + 2]].position;

        Vector3D<float> normal = (v1 - v0).CrossProduct(v2 - v0).Normalize();

        vertices[indices[i]].normal = normal;
        vertices[indices[i + 1]].normal = normal;
        vertices[indices[i + 2]].normal = normal;
    }
}

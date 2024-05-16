#include "terrain/Chunk.h"
#include "Config.h"
#include "terrain/PerlinNoise.h"
#include <iostream>


Chunk::Chunk(const int size, const std::shared_ptr<RenderConfig>& renderConfig)
	: m_size(size), m_renderConfig(renderConfig)
{
	generate_mesh(size, m_renderConfig->transform.position);
}

void Chunk::generate_mesh(int chunkSize, Vector3D<float> pos)
{
    std::vector<Vertexf> vertices;
    std::vector<unsigned int> indices;
	  auto texture = m_renderConfig->texture;
    std::vector<std::vector<float>> height_map = generate_height_map(chunkSize + 1, chunkSize + 1, heightMultiplier, scale, octaves,
                                                                    persistance, lacunarity).values;

    Color3<float> color = {1, 1, 1};
    for (int i = 0; i <= chunkSize; ++i)
    {
        for (int j = 0; j <= chunkSize; ++j)
        {
            // TODO: fix colors
            if (j % 3 == 0)
                color = {
                    static_cast<float>(rand()) / RAND_MAX, static_cast<float>(rand()) / RAND_MAX,
                    static_cast<float>(rand()) / RAND_MAX
                };
            float u = static_cast<float>(i) / static_cast<float>(chunkSize) * 5;
            float v = static_cast<float>(j) / static_cast<float>(chunkSize) * 5;
            float height = height_map[i][j];
            // TODO: remove log
            // std::cout << "Height: " << height << std::endl;
            Vertexf vertex = {
                {pos.x() + i, pos.y() + height, pos.z() - j}, {0, 1, 0}, color,
                {u, v}
            };
            vertices.push_back(vertex);
        }
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

    recalculate_normals(vertices, indices);


	  m_mesh = new Mesh(vertices, indices, m_renderConfig);
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

HeightMap Chunk::generate_height_map(int width, int height, float heightMultiplier, float scale, int octaves,
                                   float persistance, float lacunarity)
{
    std::vector<std::vector<float>> values = Chunk::generate_noise_map(width, height, scale, octaves,
                                                                       persistance, lacunarity);

    float minValue = std::numeric_limits<float>::max();
    float maxValue = std::numeric_limits<float>::min();

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            values[i][j] *= heightMultiplier;

            minValue = std::min(minValue, values[i][j]);
            maxValue = std::max(maxValue, values[i][j]);
        }
    }

    return HeightMap(values, minValue, maxValue);
}

std::vector<std::vector<float>> Chunk::generate_noise_map(int width, int height, float scale, int octaves,
                                                          float persistance,
                                                          float lacunarity)
{
    PerlinNoise pn(static_cast<unsigned int>(time(nullptr)));
    std::vector<std::vector<float>> noiseMap(width, std::vector<float>(height));
    std::vector<Vector2f> octaveOffsets(octaves);

    float maxPossibleHeight = 0;
    float amplitude = 1;
    float frequency = 1;

    for (int i = 0; i < octaves; i++)
    {
        float offsetX = static_cast<float>(GetRand(-100000, 100000));
        float offsetY = static_cast<float>(GetRand(-100000, 100000));
        octaveOffsets[i] = {offsetX, offsetY};

        maxPossibleHeight += amplitude;
        amplitude *= persistance;
    }

    float maxLocalNoiseHeight = std::numeric_limits<float>::min();
    float minLocalNoiseHeight = std::numeric_limits<float>::max();

    float halfWidth = static_cast<float>(width) / 2.f;
    float halfHeight = static_cast<float>(height) / 2.f;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            amplitude = 1;
            frequency = 1;
            float noiseHeight = 0;

            for (int i = 0; i < octaves; i++)
            {
                float sampleX = (x - halfWidth + octaveOffsets[i].x) / scale * frequency;
                float sampleY = (y - halfHeight + octaveOffsets[i].y) / scale * frequency;

                float perlinValue = static_cast<float>(pn.noise(sampleX, sampleY, 0) * 2 - 1);

                noiseHeight += perlinValue * amplitude;

                amplitude *= persistance;
                frequency *= lacunarity;
            }

            if (noiseHeight > maxLocalNoiseHeight)
            {
                maxLocalNoiseHeight = noiseHeight;
            }

            if (noiseHeight < minLocalNoiseHeight)
            {
                minLocalNoiseHeight = noiseHeight;
            }

            noiseMap[x][y] = noiseHeight;
        }
    }

    return noiseMap;
}

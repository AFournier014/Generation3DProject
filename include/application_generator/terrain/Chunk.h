#ifndef CHUNK_H
#define CHUNK_H

#include "Meshs/Mesh.h"

struct HeightMap
{
    std::vector<std::vector<float>> values;
    float minValue;
    float maxValue;

    HeightMap(const std::vector<std::vector<float>>& values, float minValue, float maxValue)
        : values(values), minValue(minValue), maxValue(maxValue)
    {
    }
};

class Chunk
{
public:
    Chunk(int size, const Vector3D<float>& position);
    Mesh* getMesh() const { return m_mesh; }
    
    bool& get_auto_update() { return auto_update; }
    float& get_height_multiplier() { return heightMultiplier; }
    float& get_scale() { return scale; }
    int& get_octaves() { return octaves; }
    float& get_persistance() { return persistance; }
    float& get_lacunarity() { return lacunarity; }
    
private:
    void generate_mesh(int chunkSize, Vector3D<float> pos);
    static void recalculate_normals(std::vector<Vertexf>& vertices, const std::vector<unsigned int>& indices);
    static HeightMap generate_height_map(int width, int height, float heightMultiplier, float scale, int octaves, float persistance, float lacunarity);
    static std::vector<std::vector<float>> generate_noise_map(int width, int height, float scale, int octaves,
                                                              float persistance, float lacunarity);

    Mesh* m_mesh;
    int m_size;
    Vector3D<float> m_position;

#pragma region TerrainSettings
    bool auto_update = true;
    float heightMultiplier = 25;
    float scale = 50;
    int octaves = 8;
    float persistance = 0.5f;
    float lacunarity = 1.5f;
#pragma endregion // TerrainSettings
};

inline float MapValue(float minimum, float maximum, float value)
{
    return minimum + (maximum - minimum) * ((value - 0) / (1 - 0));
}

inline float GetRandF(float fMin, float fMax)
{
    return (fMax - fMin) * ((((float)rand()) / (float)RAND_MAX)) + fMin;
}

inline int GetRand(int min, int max)
{
    return min + (rand() % static_cast<int>(max - min + 1));
}

#endif // APPLICATION_H

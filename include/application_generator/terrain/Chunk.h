#ifndef CHUNK_H
#define CHUNK_H

#include "Meshs/Mesh.h"

struct HeightMap;

class Chunk
{
public:
    Chunk(int size, const std::shared_ptr<RenderConfig>& renderConfig);
    void generate_mesh(HeightMap height_map, Vector3D<float> pos);
    void render() const;
    void setSize(int chunk_size);

private:
    static void recalculate_normals(std::vector<Vertexf>& vertices, const std::vector<unsigned int>& indices);

    std::unique_ptr<Mesh> m_mesh;
    int m_size;
    Vector3D<float> m_position;
    std::shared_ptr<RenderConfig> m_renderConfig;

#pragma region TerrainSettings
    bool auto_update = true;
    float heightMultiplier = 25;
    float scale = 50;
    int octaves = 8;
    float persistance = 0.5f;
    float lacunarity = 1.5f;
#pragma endregion // TerrainSettings
};

#endif // APPLICATION_H

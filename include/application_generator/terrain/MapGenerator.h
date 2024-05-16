#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H
#include <memory>

#include "Chunk.h"

struct RenderConfig;

class MapGenerator
{
public:
    MapGenerator(std::shared_ptr<RenderConfig> renderConfig);
    
    bool& get_auto_update() { return auto_update; }
    float& get_height_multiplier() { return heightMultiplier; }
    float& get_scale() { return scale; }
    int& get_octaves() { return octaves; }
    float& get_persistance() { return persistance; }
    float& get_lacunarity() { return lacunarity; }
    
    void generate_chunk_preview() const;
    void render_preview_chunk();

private:
    std::unique_ptr<Chunk> m_chunk_previw;
    std::shared_ptr<RenderConfig> renderConfig;
    
#pragma region TerrainSettings
    bool auto_update = true;
    float heightMultiplier = 25;
    float scale = 50;
    int octaves = 8;
    float persistance = 0.5f;
    float lacunarity = 1.5f;
#pragma endregion // TerrainSettings
};

#endif // MAP_GENERATOR_H

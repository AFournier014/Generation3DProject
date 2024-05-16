#ifndef MAP_GENERATOR_H
#define MAP_GENERATOR_H
#include <memory>

#include "Chunk.h"

struct RenderConfig;

class MapGenerator
{
public:
    MapGenerator(std::shared_ptr<RenderConfig> renderConfig);
    
    float& get_height_multiplier() { return heightMultiplier; }
    float& get_scale() { return scale; }
    int& get_octaves() { return octaves; }
    float& get_persistance() { return persistance; }
    float& get_lacunarity() { return lacunarity; }
    int& get_seed() { return seed; }
    bool& get_octave_randomness() { return octaveRandomness; }

    void set_height_multiplier(float value) { heightMultiplier = value; }
    void set_scale(float value) { scale = value; }
    void set_octaves(int value) { octaves = value; }
    void set_persistance(float value) { persistance = value; }
    void set_lacunarity(float value) { lacunarity = value; }
    void set_seed(int value) { seed = value; }
    void set_octave_randomness(bool value) { octaveRandomness = value; }
    
    void generate_chunk_preview() const;
    void render_preview_chunk();

private:
    std::unique_ptr<Chunk> m_chunk_preview;
    std::shared_ptr<RenderConfig> renderConfig;
    
#pragma region TerrainSettings
    bool auto_update = true;
    float heightMultiplier = 25;
    float scale = 50;
    int octaves = 8;
    float persistance = 0.5f;
    float lacunarity = 1.5f;
    int seed = 0;
    bool octaveRandomness = false;
#pragma endregion // TerrainSettings
};

#endif // MAP_GENERATOR_H

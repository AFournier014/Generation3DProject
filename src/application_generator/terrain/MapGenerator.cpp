#include "terrain/MapGenerator.h"

#include "terrain/Chunk.h"
#include "terrain/HeightMapGenerator.h"

MapGenerator::MapGenerator(std::shared_ptr<RenderConfig> renderConfig) : renderConfig(renderConfig)
{
    m_chunk_preview = std::make_unique<Chunk>(241, renderConfig);
}

void MapGenerator::generate_chunk_preview() const
{
    m_chunk_preview->generate_mesh(heightMap, renderConfig->transform.position);
    HeightMap heightMap = HeightMapGenerator::generate_height_map(242, 242, heightMultiplier, scale, octaves, persistance, lacunarity, seed);
}

void MapGenerator::render_preview_chunk()
{
    m_chunk_preview->render();
}

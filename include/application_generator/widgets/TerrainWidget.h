#pragma once
#include <imgui.h>
#include "terrain/Chunk.h"

class MapGenerator;
class TerrainWidget 
{
public:
	TerrainWidget(std::shared_ptr<MapGenerator> mapGenerator);
	~TerrainWidget() = default;

	void CreateTerrainWidgets(std::shared_ptr<MapGenerator> mapGenerator);

private:
	bool m_autoGenerate = false;
	float m_seed = 0.0f;
	float m_initialHeight = 0.0f;
	float m_initialScale = 0.0f;
	float m_initialLacunarity = 0.0f;
	float m_initialPersistance = 0.0f;
	int m_initialOctaves = 1;
};
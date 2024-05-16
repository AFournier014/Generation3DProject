#include "widgets/TerrainWidget.h"
#include "imgui.h"
#include "terrain/MapGenerator.h"

TerrainWidget::TerrainWidget(std::shared_ptr<MapGenerator> mapGenerator)
{
	m_initialHeight = mapGenerator->get_height_multiplier();
	m_initialScale = mapGenerator->get_scale();
	m_initialPersistance = mapGenerator->get_persistance();
	m_initialLacunarity = mapGenerator->get_lacunarity();
	m_initialOctaves = mapGenerator->get_octaves();
}

void TerrainWidget::CreateTerrainWidgets(std::shared_ptr<MapGenerator> mapGenerator)
{

	ImGui::Begin("Terrain Editor");
	ImGui::Checkbox("Auto Generate", &m_autoGenerate);

	bool update = false;

	if(ImGui::SliderFloat("Height", &mapGenerator->get_height_multiplier(), 0.01f, 50.f))
	{
		update = true;
	}
	if(ImGui::SliderFloat("Noise Scale", &mapGenerator->get_scale(), 1.f, 100.0f))
	{
		update = true;
	}
	if(ImGui::SliderFloat("Amplitude", &mapGenerator->get_persistance(), 0.01f, 1.0f))
	{
		update = true;
	}
	if(ImGui::SliderFloat("Frequency", &mapGenerator->get_lacunarity(), 0.01f, 2.0f))
	{
		update = true;
	}
	if(ImGui::SliderInt("Octaves", &mapGenerator->get_octaves(), 1, 10))
	{
		update = true;
	}

	if (m_autoGenerate && update)
		mapGenerator->generate_chunk_preview();

	if (!m_autoGenerate)
	{
		if (ImGui::Button("Generate"))
		{
			mapGenerator->generate_chunk_preview();
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Reset"))
	{
		mapGenerator->set_height_multiplier(m_initialHeight);
		mapGenerator->set_scale(m_initialScale);
		mapGenerator->set_persistance(m_initialPersistance);
		mapGenerator->set_lacunarity(m_initialLacunarity);
		mapGenerator->set_octaves(m_initialOctaves);
		mapGenerator->generate_chunk_preview();
	}

	ImGui::End();
}
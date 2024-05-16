#ifndef WATER_PLANE_H
#define WATER_PLANE_H

#include "meshs/Mesh.h"
#include <vector>

class WaterPlane : public Mesh
{
public:
	explicit WaterPlane(const std::shared_ptr<RenderConfig> renderConfig);

	void render() override;

private:
	std::vector<Vertexf> createVertices();
	std::vector<unsigned int> createIndices();
	GLuint createReflectionFrameBuffer(unsigned int& reflectionTexture) const;
	GLuint createRefractionFrameBuffer(unsigned int& refractionTexture) const;

	unsigned int m_reflectionTexture;
	unsigned int m_reflectionFrameBuffer;
	unsigned int m_refractionTexture;
	unsigned int m_refractionFrameBuffer;
};

#endif // !WATER_PLANE_H
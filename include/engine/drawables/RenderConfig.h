#ifndef RENDER_CONFIG_H
#define RENDER_CONFIG_H

#include "MathIncludes.h"
#include "Texture.h"
#include "Shader.h"
#include "memory"

struct RenderConfig
{
	RenderConfig() = default;

	Transform<float> m_transform;
	std::shared_ptr<Texture> m_texture;
	std::shared_ptr<Shader> m_shader;
};

#endif // RENDER_CONFIG_H
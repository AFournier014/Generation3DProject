#ifndef LIGHT_H
#define LIGHT_H

#include <memory>
#include "MathIncludes.h"
#include "Shader.h"

class Light
{
public:
	virtual void setupUniforms(std::shared_ptr<Shader> shader, int index) = 0;
};

class DirectionalLight : public Light
{
public:
	DirectionalLight(const Vector3f& direction, const Color4f& color)
		: direction(direction), color(color)
	{}

	void setupUniforms(std::shared_ptr<Shader> shader, int index) override
	{
		shader->SetUniform3f("directionalLights.direction", direction);
		shader->SetUniform4f("directionalLights.color", color.r, color.g, color.b, color.a);
	}

private:
	Vector3f direction;
	Color4f color;
	// float intensity;
};

class PointLight : public Light
{
public:
	PointLight(const Vector3f& position, const Color4f& color, float intensity)
		: m_position(position), m_color(color), m_intensity(intensity)
	{}

	void setupUniforms(std::shared_ptr<Shader> shader, int index) override
	{
		shader->SetUniform3f("pointLights.position", m_position);
		shader->SetUniform4f("pointLights.color", m_color.r, m_color.g, m_color.b, m_color.a);
		shader->SetUniform1f("pointLights.intensity", m_intensity);
	}

private:
	Vector3f m_position;
	Color4f m_color;
	float m_intensity;
};

#endif // LIGHT_H
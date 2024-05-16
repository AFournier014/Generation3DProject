#ifndef RENDER_CONFIG_H
#define RENDER_CONFIG_H

#include <memory>

class Texture;
class Shader;
class DirectionalLight;
class PointLight;
struct OpticalProperties;

struct RenderConfig
{
	RenderConfig() = default;

	Transform<float> transform;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Shader> shader;
	std::shared_ptr<DirectionalLight> directionalLight;
	std::shared_ptr<PointLight> pointLight;
	std::shared_ptr<OpticalProperties> opticalProperties;
};

#endif // RENDER_CONFIG_H
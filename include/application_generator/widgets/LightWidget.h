#pragma once
#include <imgui.h>
#include <memory>

class DirectionalLight;
struct OpticalProperties;

class LightWidget
{
public:
	LightWidget() {};
	~LightWidget() = default;

	void CreateDirectionalLightWidgets(std::shared_ptr<DirectionalLight> directionalLight);
	void CreateOpticalPropertiesWidgets(std::shared_ptr<OpticalProperties> opticalProperties);

};
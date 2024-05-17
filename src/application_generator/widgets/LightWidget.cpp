#include "widgets/LightWidget.h"
#include <memory>
#include "lights/Light.h"

void LightWidget::CreateDirectionalLightWidgets(std::shared_ptr<DirectionalLight> directionalLight)
{
	ImGui::Text("Directional Light");
	ImGui::Text("Direction:");
	ImGui::SliderFloat("X", &directionalLight->getDirection().x(), -1.0f, 1.0f);
	ImGui::SliderFloat("Y", &directionalLight->getDirection().y(), -1.0f, 1.0f);
	ImGui::SliderFloat("Z", &directionalLight->getDirection().z(), -1.0f, 1.0f);

	ImGui::Text("Color");
	ImGui::SliderFloat("Red", &directionalLight->getColor().r, 0.0f, 255.0f);
	ImGui::SliderFloat("Blue", &directionalLight->getColor().b, 0.0f, 255.0f);
	ImGui::SliderFloat("Green", &directionalLight->getColor().g, 0.0f, 255.0f);
}

void LightWidget::CreateOpticalPropertiesWidgets(std::shared_ptr<OpticalProperties> opticalProperties)
{
	ImGui::Text("Optical Properties");
	/*ImGui::ColorEdit3("Color", &opticalProperties->color[0]);*/
	ImGui::SliderFloat("Ambient", &opticalProperties->ambient, 0.0f, 1.0f);
	ImGui::SliderFloat("Diffuse", &opticalProperties->diffuse, 0.0f, 1.0f);
	ImGui::SliderFloat("Specular", &opticalProperties->specular, 0.0f, 1.0f);
	ImGui::SliderFloat("Shininess", &opticalProperties->shininess, 1.0f, 128.0f);
}

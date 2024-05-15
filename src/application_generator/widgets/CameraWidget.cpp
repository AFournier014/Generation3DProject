#include "CameraWidget.h"
#include "Config.h"

void CameraWidget::CreateCameraWidgets(std::shared_ptr<Camera> camera) {
    ImGui::Begin("Camera Controls");

    // Camera control widgets
    ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", camera->getPosition().x(), camera->getPosition().y(), camera->getPosition().z());

    ImGui::SliderFloat("Camera Speed", &camera->getSpeed(), 10.f, 100.f);
	ImGui::SliderFloat("Camera Sensitivity", &camera->getSensitivity(), 0.001f, .01f);

	ImGui::Text("Camera FOV", camera->getFov());

    if (ImGui::SliderFloat("FOV", &camera->getFov(), 10.f*3.14f/180.f, 120.f * 3.14f / 180.f))
    {
        camera->updateProjectionMatrix();
    }
	if (ImGui::Button("Reset Default"))
    {
		float defaultFOV = Config::GetCameraFov();

		camera->setFov(defaultFOV);
		camera->SetSpeed(30.f);
		camera->SetSensivity(0.005f);
		camera->updateProjectionMatrix();
	}


    ImGui::End();
}
#include "CameraWidget.h"
#include "Config.h"

void CameraWidget::CreateCameraWidgets(std::shared_ptr<Camera> camera) {
    ImGui::Begin("Camera Controls");

    // Camera control widgets
    ImGui::Text("Position: (%.2f, %.2f, %.2f)", camera->getPosition().x(), camera->getPosition().y(), camera->getPosition().z());
    ImGui::Text("Front: (%.2f, %.2f, %.2f)", camera->getFront().x(), camera->getFront().y(), camera->getFront().z());
    ImGui::Text("Pitch: %.2f | Yaw: %.2f%", camera->getPitch(), camera->getYaw());

    ImGui::SliderFloat("Speed", &camera->getSpeed(), 10.f, 150.f);
	ImGui::SliderFloat("Sensitivity", &camera->getSensitivity(), 0.001f, .01f);

    if (ImGui::SliderFloat("FOV", &camera->getFov(), 10.f*3.14f/180.f, 120.f * 3.14f / 180.f))
    {
        camera->updateProjectionMatrix();
    }
    ImGui::SameLine();
    ImGui::Text("%.1f", camera->getFov() * 180.f / 3.14f);

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
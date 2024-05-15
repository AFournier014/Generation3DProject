#include "CameraWidget.h"

void CameraWidget::CreateCameraWidgets(std::shared_ptr<Camera> camera) {
    ImGui::Begin("Camera Controls");

    // Camera control widgets
    ImGui::Text("Camera Position: (%.2f, %.2f, %.2f)", camera->getPosition().x(), camera->getPosition().y(), camera->getPosition().z());
    ImGui::SliderFloat("Camera Speed", &camera->getSpeed(), 10.f, 100.f);
	ImGui::SliderFloat("Camera Sensitivity", &camera->getSensitivity(), 0.001f, .01f);
	ImGui::SliderFloat("Camera FOV", &camera->getFov(), 45.0f, 100.0f);

    ImGui::End();
}
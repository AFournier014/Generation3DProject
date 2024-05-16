#include "widgets/CameraWidget.h"
#include "Config.h"

CameraWidget::CameraWidget(std::shared_ptr<Camera> camera)
{
    m_camera = camera;
    m_initialFar = camera->getFarPlane();
    m_initialNear = camera->getNearPlane();
    m_initialSensitivity = camera->getSensitivity();
    m_initialSpeed = camera->getSpeed();
}

void CameraWidget::CreateCameraWidgets(std::shared_ptr<Camera> camera) {
    ImGui::Begin("Camera Controls");

    // Camera control widgets
    ImGui::Text("Position: (%.2f, %.2f, %.2f)", camera->getPosition().x(), camera->getPosition().y(), camera->getPosition().z());
    ImGui::Text("Front: (%.2f, %.2f, %.2f)", camera->getFront().x(), camera->getFront().y(), camera->getFront().z());
    ImGui::Text("Pitch: %.2f | Yaw: %.2f%", camera->getPitch(), camera->getYaw());

    ImGui::SliderFloat("Speed", &camera->getSpeed(), 10.f, 100.f);
	ImGui::SliderFloat("Sensitivity", &camera->getSensitivity(), 0.001f, .01f);

    if(ImGui::SliderFloat("Near Plane", &camera->getNearPlane(), 0.1f, 100.f))
    {
        camera->updateProjectionMatrix();
    }

    if (ImGui::SliderFloat("Far Plane", &camera->getFarPlane(), 100.f, 1000.f))
    {
        camera->updateProjectionMatrix();
    }

    if (ImGui::SliderFloat("FOV", &camera->getFov(), 10.f * 3.14f / 180.f, 120.f * 3.14f / 180.f))
    {
        camera->updateProjectionMatrix();
    }
    ImGui::SameLine();
    ImGui::Text("%.1f", camera->getFov() * 180.f / 3.14f);

	if (ImGui::Button("Reset Default"))
    {
		float defaultFOV = Config::GetCameraFov();

		camera->setFov(defaultFOV);
		camera->SetSpeed(m_initialSpeed);
		camera->SetSensivity(m_initialSensitivity);
        camera->setNearPlane(m_initialNear);
        camera->setFarPlane(m_initialFar);
		camera->updateProjectionMatrix();
	}
    ImGui::End();
}
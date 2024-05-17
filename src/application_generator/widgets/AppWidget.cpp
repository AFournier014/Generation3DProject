#include "widgets/AppWidget.h"

void AppWidget::CreateAppWidgets(float deltaTime)
{
	static int frameCount = 0;
	static int displayInterval = 6;
    ImGui::Begin("FPS Display");

    ImGui::Text("Application FPS: %.1f", m_fps);
	if (frameCount >= displayInterval)
    {
		m_fps = 1/deltaTime;
		frameCount = 0;
	}
	frameCount++;

    ImGui::End();
}

#include "widgets/AppWidget.h"

#include <GL/glew.h>

void AppWidget::CreateAppWidgets(float deltaTime)
{
	static int frameCount = 0;
	static int displayInterval = 6;
    ImGui::Begin("App settings");

	ImGui::Checkbox("Wireframe", &m_wireframe);

	
    ImGui::Text("Application FPS: %.1f", m_fps);
	if (frameCount >= displayInterval)
    {
		m_fps = 1/deltaTime;
		frameCount = 0;
	}
	frameCount++;

	if (m_wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
    ImGui::End();
}

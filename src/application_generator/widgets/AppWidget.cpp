#include "AppWidget.h"

void AppWidget::CreateAppWidgets(float deltaTime)
{
    ImGui::Begin("FPS Display");
    ImGui::Text("Application FPS: %.1f", 1/deltaTime);
    ImGui::End();
}

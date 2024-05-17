#pragma once
#include <imgui.h>

class AppWidget 
{
public:
	AppWidget() = default;
	~AppWidget() = default;

	void CreateAppWidgets(float deltaTime);
private:
	float m_fps = 0.0f;
};
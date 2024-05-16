#pragma once
#include <imgui.h>
#include "Camera.h"

class CameraWidget{
public:
    CameraWidget(std::shared_ptr<Camera> camera) ;
    ~CameraWidget() = default;

    void CreateCameraWidgets(std::shared_ptr<Camera> camera);

private:
    float m_initialSpeed;
    float m_initialSensitivity;
    float m_initialNear;
    float m_initialFar;

    std::shared_ptr<Camera> m_camera;
};
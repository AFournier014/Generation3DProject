#pragma once
#include <imgui.h>
#include "Camera.h"

class CameraWidget{
public:
    CameraWidget() = default;
    ~CameraWidget() = default;

    void CreateCameraWidgets(std::shared_ptr<Camera> camera);
};
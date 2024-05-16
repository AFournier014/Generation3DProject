#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <memory>

class ImGuiManager {
public:
    ImGuiManager(GLFWwindow* window, const char* glslVersion);
    ~ImGuiManager();

    void Initialize();
    void BeginFrame();
    void EndFrame();
    void Shutdown();

private:
    GLFWwindow* m_window;
    const char* m_glslVersion;
};

#endif // IMGUI_MANAGER_H
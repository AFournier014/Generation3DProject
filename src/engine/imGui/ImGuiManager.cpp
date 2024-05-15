#include "imGui/ImGuiManager.h"

ImGuiManager::ImGuiManager(GLFWwindow* window, const char* glslVersion)
    : m_window(window), m_glslVersion(glslVersion) {}

ImGuiManager::~ImGuiManager() 
{
}

void ImGuiManager::Initialize() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(m_glslVersion);
    ImGui::StyleColorsDark();
}

void ImGuiManager::BeginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGuiManager::EndFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiManager::Shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
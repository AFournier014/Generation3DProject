#ifndef CONFIG_H
#define CONFIG_H

#include "MathIncludes.h"
#include <string>
#include <GLFW/glfw3.h>

using Mat4f = Mat4<float>;
using Vec2i = Vector2D<int>;
using Vec2f = Vector2D<float>;
using Vec2u = Vector2D<unsigned int>;
using Vec3f = Vector3D<float>;
using Transformf = Transform<float>;

namespace Config
{
	constexpr unsigned int WindowWidth = 1920;
	constexpr unsigned int WindowHeight = 1080;

	constexpr int CameraForward = GLFW_KEY_W;
	constexpr int CameraBackward = GLFW_KEY_S;
	constexpr int CameraLeft = GLFW_KEY_A;
	constexpr int CameraRight = GLFW_KEY_D;

	constexpr float CameraFov = 45.f;
	constexpr float CameraNear = 0.1f;
	constexpr float CameraFar = 100.f;

	constexpr float CameraSpeed = 0.1f;
	constexpr float CameraRotationSpeed = 0.1f;
	
	constexpr float CameraInitialPositionX = 5.f;
	constexpr float CameraInitialPositionY = 50.f;
	constexpr float CameraInitialPositionZ = -5.f;

	constexpr float CameraInitialYaw = -0.5f;
	constexpr float CameraInitialPitch = 7.f;

	inline const std::string SHADERS_PATH = "resources/shaders/";
	inline const std::string ASSETS_PATH = "resources/assets/";
	inline const std::string TEXTURES_PATH = "resources/textures/";
	inline const std::string FONT_PATH = "resources/fonts/";

	inline const std::string ApplicationName = "Generator 3D Project";

	inline const std::string TriangleVertexShaderPath = SHADERS_PATH + "triangle.vert";
	inline const std::string TriangleFragmentShaderPath = SHADERS_PATH + "triangle.frag";
	inline const std::string CubeVertexShaderPath = SHADERS_PATH + "cube.vert";
	inline const std::string CubeFragmentShaderPath = SHADERS_PATH + "cube.frag";
	inline const std::string SkyphereVertexShaderPath = SHADERS_PATH + "skyphere.vert";
	inline const std::string SkyphereFragmentShaderPath = SHADERS_PATH + "skyphere.frag";

	inline const std::string ArialFontPath = FONT_PATH + "ARIAL.ttf";

	inline Vec2u WindowSize()
	{
		return Vec2u(WindowWidth, WindowHeight);
	}

	inline Vec3f CameraInitialPosition()
	{
		return Vec3f(CameraInitialPositionX, CameraInitialPositionY, CameraInitialPositionZ);
	}

	inline Vec2f CameraInitialRotation()
	{
		return Vec2f(CameraInitialPitch, CameraInitialYaw);
	}

	inline float GetAspectRatio()
	{
		return static_cast<float>(WindowSize().x) / static_cast<float>(WindowSize().y);
	}

	inline float GetCameraFov()
	{
		return CameraFov / 180.f * 3.14159265359f;
	}
}

#endif // CONFIG_H
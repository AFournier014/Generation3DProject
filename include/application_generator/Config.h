#ifndef CONFIG_H
#define CONFIG_H

#include "Vector.h"
#include "Matrice.h"
#include <string>

using Mat4f = Mat4<float>;
using Vec2i = Vector2D<int>;
using Vec2f = Vector2D<float>;
using Vec2u = Vector2D<unsigned int>;
using Vec3f = Vector3D<float>;

namespace Config
{
	constexpr unsigned int WindowWidth = 1280;
	constexpr unsigned int WindowHeight = 720;

	constexpr int ContextSettingsDepthBits = 24;
	constexpr int ContextSettingsStencilBits = 8;
	constexpr int ContextSettingsAntialiasingLevel = 4;
	constexpr int ContextSettingsMajorVersion = 4;
	constexpr int ContextSettingsMinorVersion = 6;

	constexpr float CameraFov = 45.f;
	constexpr float CameraNear = 0.1f;
	constexpr float CameraFar = 100.f;

	constexpr float CameraSpeed = 0.1f;
	constexpr float CameraRotationSpeed = 0.1f;
	
	constexpr float CameraInitialPositionX = 0.f;
	constexpr float CameraInitialPositionY = 0.f;
	constexpr float CameraInitialPositionZ = 0.f;

	inline const std::string SHADERS_PATH = "resources/shaders/";
	inline const std::string ASSETS_PATH = "resources/assets/";
	inline const std::string TEXTURES_PATH = "resources/textures/";

	inline const std::string ApplicationName = "Generator 3D Project";
	inline const std::string TriangleVertexShaderPath = SHADERS_PATH + "triangle.vert";
	inline const std::string TriangleFragmentShaderPath = SHADERS_PATH + "triangle.frag";
	inline const std::string CubeVertexShaderPath = SHADERS_PATH + "cube.vert";
	inline const std::string CubeFragmentShaderPath = SHADERS_PATH + "cube.frag";

	inline Vec2u WindowSize()
	{
		return Vec2u(WindowWidth, WindowHeight);
	}

	inline Vec3f CameraInitialPosition()
	{
		return Vec3f(CameraInitialPositionX, CameraInitialPositionY, CameraInitialPositionZ);
	}
}

#endif // CONFIG_H
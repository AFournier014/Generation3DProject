#pragma once

template <typename T>
class Drawable
{
public:
	~Drawable() = default;
	virtual void update() = 0;
	virtual void render(Shader& shader, const Mat4<T>& VP, const Point3D<T>& cameraPositionWorld) = 0;
};
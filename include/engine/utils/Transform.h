#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.h"

template<typename T>
struct Transform
{
	Transform(const Vector3D<T>& position_ = Vector3D<T>(), const Mat4<T>& rotation_ = Mat4<T>(), const Vector3D<T>& scale_ = Vector3D<T>())
		: position(position_), rotation(rotation_), scale(scale_)
	{}

	Transform(const Transform& transform)
		: position(transform.position), rotation(transform.rotation), scale(transform.scale)
	{}

	Transform<T> operator+(const Transform<T>& transform) const
	{
		return Transform<T>{position + transform.position, rotation + transform.rotation, scale + transform.scale};
	}

	Transform<T> operator-(const Transform<T>& transform) const
	{
		return Transform<T>{position - transform.position, rotation - transform.rotation, scale - transform.scale};
	}

	Transform<T> operator*(const T& scalar) const
	{
		return Transform<T>{position* scalar, rotation* scalar, scale* scalar};
	}

	Transform<T>& operator+=(const Transform<T>& transform)
	{
		position += transform.position;
		rotation += transform.rotation;
		scale += transform.scale;
		return *this;
	}

	Transform<T>& operator-=(const Transform<T>& transform)
	{
		position -= transform.position;
		rotation -= transform.rotation;
		scale -= transform.scale;
		return *this;
	}

	Transform<T>& operator*=(const T& scalar)
	{
		position *= scalar;
		rotation *= scalar;
		scale *= scalar;
		return *this;
	}

	bool operator==(const Transform& other) const = default;

	T* data()
	{
		return position.data();
	}

	const T* data() const
	{
		return position.data();
	}

	Vector3D<T> position;
	Mat4<T> rotation;
	Vector3D<T> scale;
};

#endif // TRANSFORM_H
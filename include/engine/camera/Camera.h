#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <GL/glew.h>

#include <MathIncludes.h>
#include<cmath>
#include <string>


#define _USE_MATH_DEFINES

class Camera
{

public:
	Camera(const Vector3f& position, const float aspect, const float fov, const float near, const float far);
	~Camera() = default;

	void mouseMoved(double xpos, double ypos);
	void mouseWheelMoved(double x, double y);

	inline void SetSpeed(const float& speed) { m_speed = speed; }
	inline void SetSensivity(const float& sensivity) { m_sensivity = sensivity; }
	void SetPosition(const Vector3f& position);

	void update(float timestep);

	void VectorsFromAngles();
	Mat4<float> GetProjectionViewMatrix() const { return Projection * View; }
	Vector3f GetPosition() const { return m_position; }
	void SetProjection(float aspect, float fov, float near, float far);

	void moveLeft(float multiplier = 1.f) { m_position += m_left * m_velocity * multiplier; }
	void moveRight(float multiplier = 1.f) { m_position -= m_left * m_velocity * multiplier; }
	void moveForward(float multiplier = 1.f) { m_position += m_forward * m_velocity * multiplier; }
	void moveBackward(float multiplier = 1.f) { m_position -= m_forward * m_velocity * multiplier; }

	void toggleRotation() {};

private:
	//Main values
	float m_speed;
	float m_sensivity;
	float m_alpha;
	float m_beta;

	Vector2f old_Pos;

	float m_velocity;

	float m_fov;

	//Vertical motion
	double m_timeBeforeStoppingVerticalMotion;
	bool m_verticalMotionActive = false;
	bool m_isSpeedingUp = false;
	float m_verticalMotionDirection;

	Mat4<float> Projection;
	Mat4<float> View;

	//Vectors
	Vector3f m_position;
	Vector3f m_target;
	Vector3f m_forward;
	Vector3f m_left;
	Vector3f m_up;
};

#endif // !CAMERA_H
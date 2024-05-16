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

	void setProjection(float aspect, float fov, float near, float far);
	void updateProjectionMatrix();

	Mat4<float> getProjectionViewMatrix() const { return Projection * View; }
	Vector3f getPosition() const { return m_position; }

	Vector3f getFront() const { return m_forward; }
	Vector3f getLeft() const { return m_left; }

	void setDirection(Vector3f direction) { m_direction = direction;}

	float getPitch() const { return m_pitch; }
	float getYaw() const { return m_yaw; }
	float& getSpeed() { return m_speed; }
	float& getSensitivity() { return m_sensivity; }
	float& getFov() { return m_fov; }

	void setFov(float fov) { m_fov = fov; updateProjectionMatrix();}
	void setAspectRatio(float aspect) { m_aspectRatio = aspect; updateProjectionMatrix(); }
	void setRotation(Vector2f rotation) { m_pitch = rotation.x; m_yaw = rotation.y; VectorsFromAngles(); }
	void toggleRotation() {};

private:
	//Main values
	float m_speed;
	float m_sensivity;
	float m_pitch;
	float m_yaw;

	Vector2f old_Pos;

	float m_velocity;

	float m_fov;
	float m_near;
	float m_far;
	float m_aspectRatio;


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
	Vector3f m_direction;
};

#endif // !CAMERA_H
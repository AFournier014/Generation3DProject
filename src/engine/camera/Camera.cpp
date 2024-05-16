#include "camera/Camera.h"

#include <algorithm>

Camera::Camera(const Vector3f& position = Vector3f(0, 0, 0), const float aspect = 1.f, const float fov = 70.0f, const float near = 0.1f, const float far = 1000.f)
	: m_speed(30.f), m_sensivity(0.005f), m_pitch(.0f), m_yaw(.0f), m_position(position)
{
	Projection = Mat4<float>::Identity();
	m_forward = Vector3f(0, 0, 1);
	m_left = Vector3f(1, 0, 0);
	m_up = Vector3f(0, 1, 0);

	setProjection(aspect, fov, near, far);
}

void Camera::setProjection(float aspect, float fov, float near, float far)
{
	Projection = Mat4<float>::Projection(aspect, fov, near, far);
	m_aspectRatio = aspect;
	m_fov = fov;
	m_near = near;
	m_far = far;
}

void Camera::updateProjectionMatrix()
{
	Projection = Mat4<float>::Projection(m_aspectRatio, m_fov, m_near, m_far);
}


void Camera::mouseMoved(double xpos, double ypos)
{
	float xOffset = static_cast<float>(xpos);
	float yOffset = static_cast<float>(ypos);

	m_pitch += xOffset * m_sensivity;
	m_yaw -= yOffset * m_sensivity;

	constexpr float maxPitch = 1.570796f; // 90 degr�s en radians
	m_yaw = std::clamp(m_yaw, -maxPitch, maxPitch);

	// Recalcule les vecteurs de la camera en fonction des angles
	VectorsFromAngles();
}

void Camera::update(float timestep)
{
	m_velocity = m_speed;
	m_velocity *= timestep;

	if (m_verticalMotionActive)
	{
		m_timeBeforeStoppingVerticalMotion -= timestep;
		if (m_timeBeforeStoppingVerticalMotion <= 0)
		{
			m_verticalMotionActive = false;
			m_timeBeforeStoppingVerticalMotion = 0;
		}
		else
			m_position.y() += m_verticalMotionDirection * m_speed * timestep;
	}

	VectorsFromAngles();

	m_position += m_direction * m_velocity;
	m_target = m_position + m_forward;

	View = Mat4<float>::RotationX(-m_yaw) * Mat4<float>::RotationY(-m_pitch) * Mat4<float>::Translation(-m_position);
}

void Camera::mouseWheelMoved(double x, double y)
{
	x;
	y;
	//if ( m_fov >= 1.0f && m_fov <= 70.0f) //coup de molette vers le haut
	//{
	//	m_fov -= static_cast<float>(y);
	//}
	//if (m_fov <= 1.0f)
	//{
	//	m_fov = 1.0f;
	//}
	//if (m_fov >= 70.0f)
	//{
	//	m_fov = 70.0f;
	//}
	//SetProjection(1.0f, m_fov, 0.1f, 1000.0f);
}


void Camera::SetPosition(const Vector3f& position)
{
	m_position = position;
	m_target = m_position + m_forward;
}


void Camera::VectorsFromAngles()
{
	Vector3f up(0, 1, 0);

	m_forward.x() = sin(m_pitch) * cos(m_yaw);
	m_forward.y() = sin(m_yaw);
	m_forward.z() = -cos(m_yaw) * cos(m_pitch);
	m_forward.Normalize();

	m_left = up.CrossProduct(m_forward);
	m_left.Normalize();

	m_up = m_forward.CrossProduct(m_left);
	m_up.Normalize();

}
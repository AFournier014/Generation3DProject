#include "camera/Camera.h"

Vector2f old_Pos;

Camera::Camera(const Vector3f& position = Vector3f(0, 0, 0), const float aspect = 1.f, const float fov = 70.0f, const float near = 0.1f, const float far = 1000.f)
    : m_speed(0.000001f), m_sensivity(0.000002f), m_alpha(.0f), m_beta(.0f), m_position(position)
{
	Projection = Mat4<float>::Identity();
	m_forward = Vector3f(0, 0, 1);
	m_left = Vector3f(1, 0, 0);
	m_up = Vector3f(0, 1, 0);

	InitProjection(aspect, fov, near, far);
}

void Camera::InitProjection(float aspect, float fov, float near, float far)
{
	Projection = Mat4<float>::Projection(aspect, fov, near, far);
}

void Camera::on_notify(const EventBase& _eventB)
{
	if (_eventB.id == "MouseMoved")
	{
		MouseMoved(Vector2f(sf::Mouse::getPosition().x - old_Pos.x, sf::Mouse::getPosition().y - old_Pos.y));
	}
	else if (_eventB.id == "Z_KeyPressed")
	{
		MoveForward();
	}
	else if (_eventB.id == "S_KeyPressed")
	{
		MoveBackward();
	}
	else if (_eventB.id == "Q_KeyPressed")
	{
		MoveLeft();
	}
	else if (_eventB.id == "D_KeyPressed")
	{
		MoveRight();
	}
	else if (_eventB.id == "LShift_KeyPressed")
    {
		m_isSpeedingUp = true;
	}
    else
	{
        m_isSpeedingUp = false;
	}
}

void Camera::MouseMoved(Vector2f pos)
{
    m_alpha += pos.x  * m_sensivity;
    m_beta -= pos.y  * m_sensivity;;
    old_Pos = pos;
}

void Camera::update(float timestep)
{
    m_velocity = m_isSpeedingUp ? m_speedMultiplier * m_speed : m_speed;
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

    m_target = m_position + m_forward;

    View = Mat4<float>::RotationX(-m_beta) * Mat4<float>::RotationY(-m_alpha) * Mat4<float>::Translation(-m_position);
}

void Camera::MouseWheelMoved(const sf::Event& event)
{
    if (event.mouseWheel.delta > 0) //coup de molette vers le haut
    {
        m_verticalMotionActive = true;
        m_timeBeforeStoppingVerticalMotion = 0.100;
        m_verticalMotionDirection = 1;
    }
    else if (event.mouseWheel.delta < 0) //coup de molette vers le bas
    {
        m_verticalMotionActive = true;
        m_timeBeforeStoppingVerticalMotion = 0.100;
        m_verticalMotionDirection = -1;
    }
}


void Camera::SetPosition(const Vector3f& position)
{
    m_position = position;
    m_target = m_position + m_forward;
}


void Camera::VectorsFromAngles()
{
    Vector3f up(0, 1, 0);

    if (m_beta > 90)
        m_beta = 90;
    else if (m_beta < -90)
        m_beta = -90;

    m_forward.z() = std::cos(m_alpha) * std::cos(m_beta);
    m_forward.y() = std::sin(m_beta);
    m_forward.x() = std::sin(m_alpha)  * std::cos(m_beta);

	m_forward.Normalize();
    m_left = -m_forward.CrossProduct(up);
    m_left.Normalize();

	//m_up = m_left.CrossProduct(m_forward);
	//m_up.Normalize();
}


void Camera::Look()
{
    gluLookAt(m_position.x(), m_position.y(), m_position.z(),
         m_target.x(), m_target.y(), m_target.z(),
         0, 1, 0);
}


Camera::~Camera()
{  }
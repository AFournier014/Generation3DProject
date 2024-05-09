#include "camera/Camera.h"

Vector2f old_Pos;

Camera::Camera(const Vector3f& position)
    : m_speed(0.000001f), m_sensivity(0.0002f), m_alpha(.0f), m_beta(.0f), m_position(position)
{
    VectorsFromAngles();
	Projection = Mat4<float>::Identity();
	m_forward = Vector3f(0, 0, -1);
	m_left = Vector3f(-1, 0, 0);
}

void Camera::InitProjection(float aspect, float fov, float near, float far)
{
	Projection = Mat4<float>::Projection(aspect, fov, near, far);
}

void Camera::MouseMoved(Vector2f pos)
{
    m_alpha += pos.x  * m_sensivity;
    m_beta -= pos.y  * m_sensivity;

    old_Pos = pos;
    VectorsFromAngles();
}

void Camera::Update(float timestep)
{
    float currentSpeed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? 2 * m_speed : m_speed;
    VectorsFromAngles();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) m_position += m_forward * currentSpeed * timestep;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) m_position -= m_forward * currentSpeed * timestep;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) m_position += m_left * currentSpeed * timestep;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_position -= m_left * currentSpeed * timestep;

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

    float r_temp = float (std::cos((m_beta * 3.14f) / 180));
    m_forward.y() = std::sin((m_beta * 3.14f) / 180);
    m_forward.x() = r_temp * std::cos((m_alpha * 3.14f) / 180);
    m_forward.z() = r_temp * std::sin((m_alpha * 3.14f) / 180);

    m_left = up.CrossProduct(m_forward);
    m_left.Normalize();

    m_target = m_position + m_forward;
}


void Camera::Look()
{
    gluLookAt(m_position.x(), m_position.y(), m_position.z(),
         m_target.x(), m_target.y(), m_target.z(),
         0, 1, 0);
}


Camera::~Camera()
{  }
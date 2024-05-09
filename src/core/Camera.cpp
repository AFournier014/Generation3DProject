#include "Camera.hpp"

sf::Vector2i old_Pos;

Camera::Camera(const sf::Vector3f& position)
    : _speed(50), _sensivity(0.2f), _theta(0), _phi(0), _position(position)
{
    VectorsFromAngles();
}

void Camera::MouseMoved()
{
    sf::Vector2i Pos = sf::Mouse::getPosition();

    _theta += (Pos.x - old_Pos.x) * _sensivity;
    _phi -= (Pos.y - old_Pos.y) * _sensivity;

    old_Pos = Pos;
    VectorsFromAngles();
}

void Camera::Update(float timestep)
{
    float currentSpeed = (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) ? 2 * _speed : _speed;
    VectorsFromAngles();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) _position += _forward * currentSpeed * timestep;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) _position -= _forward * currentSpeed * timestep;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) _position += _left * currentSpeed * timestep;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _position -= _left * currentSpeed * timestep;

    if (_verticalMotionActive)
    {
        _timeBeforeStoppingVerticalMotion -= timestep;
        if (_timeBeforeStoppingVerticalMotion <= 0)
        {
            _verticalMotionActive = false;
            _timeBeforeStoppingVerticalMotion = 0;
        }
        else
            _position.y += _verticalMotionDirection * _speed * timestep;
    }

    _target = _position + _forward;
}

void Camera::MouseWheelMoved(const sf::Event& event)
{
    if (event.mouseWheel.delta > 0) //coup de molette vers le haut
    {
        _verticalMotionActive = true;
        _timeBeforeStoppingVerticalMotion = 0.100;
        _verticalMotionDirection = 1;
    }
    else if (event.mouseWheel.delta < 0) //coup de molette vers le bas
    {
        _verticalMotionActive = true;
        _timeBeforeStoppingVerticalMotion = 0.100;
        _verticalMotionDirection = -1;
    }
}


void Camera::SetPosition(const sf::Vector3f& position)
{
    _position = position;
    _target = _position + _forward;
}


void Camera::VectorsFromAngles()
{
    static const sf::Vector3f up(0, 1, 0);

    float r_temp = float (std::cos((_phi * 3.14f) / 180));
    _forward.z = std::sin((_phi * 3.14f) / 180);
    _forward.x = r_temp * std::cos((_theta * 3.14f) / 180);
    _forward.y = r_temp * std::sin((_theta * 3.14f) / 180);

    //_left = up.crossProduct(_forward);
    //_left.normalize();

    _target = _position + _forward;
}


void Camera::Look()
{
    gluLookAt(_position.x, _position.y, _position.z,
         _target.x, _target.y, _target.z,
         0, 1, 0);
}


Camera::~Camera()
{  }
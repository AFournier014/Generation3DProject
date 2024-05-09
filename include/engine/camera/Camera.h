#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <GL/glew.h>

#include<cmath>

#include <string>

#define _USE_MATH_DEFINES

class Camera
{

public:
	Camera(const sf::Vector3f& position = sf::Vector3f(0, 0, 0));
	virtual ~Camera();

	void MouseMoved();
	void MouseWheelMoved(const sf::Event& event);

	inline void SetSpeed(const float& speed) { _speed = speed; }
	inline void SetSensivity(const float& sensivity) { _sensivity = sensivity; }
	void SetPosition(const sf::Vector3f& position);

	void Look();
	void Update(float timestep);

	void VectorsFromAngles();

private:
	//Main values
	float _speed;
	float _sensivity;
	float _theta;
	float _phi;

	//Vertical motion
	double _timeBeforeStoppingVerticalMotion;
	bool _verticalMotionActive;
	int _verticalMotionDirection;

	//Vectors
	sf::Vector3f _position;
	sf::Vector3f _target;
	sf::Vector3f _forward;
	sf::Vector3f _left;
};
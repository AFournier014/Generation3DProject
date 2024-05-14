#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <GL/glew.h>

#include <MathIncludes.h>
#include<cmath>
#include <string>

#include "events/Events.h"

#define _USE_MATH_DEFINES

class Camera : public EventSubscriber
{

public:
	Camera(const Vector3f& position, const float aspect, const float fov, const float near, const float far);
	virtual ~Camera();

	void MouseMoved(Vector2f pos);
	void MouseWheelMoved(const sf::Event& event);

	inline void SetSpeed(const float& speed) { m_speed = speed; }
	inline void SetSensivity(const float& sensivity) { m_sensivity = sensivity; }
	void SetPosition(const Vector3f& position);

	void Look();
	void Update(float timestep);

	void VectorsFromAngles();
	Mat4<float> GetProjectionViewMatrix() { return Projection * View; }
	Vector3f GetPosition() { return m_position; }
	void InitProjection(float aspect, float fov, float near, float far);

	void on_notify(const EventBase& _eventB) override;

private:
	//Main values
	float m_speed;
	float m_sensivity;
	float m_alpha;
	float m_beta;

	//Vertical motion
	double m_timeBeforeStoppingVerticalMotion;
	bool m_verticalMotionActive = false;
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
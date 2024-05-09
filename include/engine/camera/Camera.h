#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <GL/glew.h>
#include <MathIncludes.h>
#include<cmath>

#include <string>

#define _USE_MATH_DEFINES

using Vector3f = Vector3D<float>;
using Vector2f = Vector2D<float>;

class Camera
{

public:
	Camera(const Vector3f& position = Vector3f(0, 0, 0));
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
	void InitProjection(float aspect, float fov, float near, float far);

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
};
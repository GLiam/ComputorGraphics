#pragma once
#include "Camera.h"

class FirstPersonCamera : public Camera
{
public:
	void update(GLFWwindow* window, float dt) override;

	float getMoveSpeed() const { return m_moveSpeed; }
	void setMoveSpeed(float value) { m_moveSpeed = value; }

private:
	float m_moveSpeed = 1;
};
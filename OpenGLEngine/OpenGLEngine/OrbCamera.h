#pragma once
#include "Camera.h"
#include <glm\ext.hpp>

class OrbitCamera : public Camera
{
	OrbitCamera() = default;
	OrbitCamera(const glm::vec3 position,
		const glm::vec3 tragetLocation,
		float rotationSpeed = 0.2f)
	{

	}

	void setOrbit(glm::vec3 position,
		glm::vec3 targetLocation,
		float rotationSpeed);

	void update(float deltaTime);

private:
	glm::vec3 m_LookAt;
	glm::vec3 m_OffSet;
	float m_rotatSpeed;
};
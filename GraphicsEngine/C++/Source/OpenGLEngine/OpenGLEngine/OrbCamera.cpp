#include "OrbCamera.h"


void OrbitCamera::setOrbit(glm::vec3 position, glm::vec3 targetLocation, float rotationSpeed)
{
	m_LookAt = targetLocation;
	m_OffSet = position - targetLocation;
	m_rotatSpeed = rotationSpeed;
}

void OrbitCamera::update(float deltaTime)
{
	auto rotation = glm::angleAxis(m_rotatSpeed * deltaTime, glm::vec3{ 0, 1, 0 });
	m_OffSet = glm::mat4_cast(rotation) * glm::vec4{ m_OffSet, 0 };
	setLookAt(m_LookAt + m_OffSet, m_LookAt);
}

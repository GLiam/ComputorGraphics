#include "Camera.h"

void Camera::setPosition(glm::vec4 position)
{
	m_worldTransform[3] = position;
}

glm::vec4 Camera::getPosition() const
{
	return m_worldTransform[3];
}

void Camera::Translate(glm::vec4 positionModifier)
{
	m_worldTransform[3] += positionModifier;
}

void Camera::setProjectionMatrix()
{

}

void Camera::setLookAt(glm::vec3 from, glm::vec3 to)
{

}

const glm::mat4 & Camera::getProjectionMatrix() const
{
	assert(m_hasSetProjectionMatrix == true);
	return m_projectionMatrix;
}

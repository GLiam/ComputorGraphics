#pragma once
#pragma warning( push )
#pragma warning( disable : 4201)
#pragma warning( disable : 4310)
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#pragma warning( pop )


class Camera
{
public:
	void setPosition(glm::vec4 position);
	glm::vec4 getPosition() const;

	void Translate(glm::vec4 positionModifier);

	const glm::mat4& getTransform() const { return m_worldTransform; }
	glm::mat4& getTransform() { return m_worldTransform; }

	glm::mat4 getViewMatrix() const { return glm::inverse(m_worldTransform); }

	void setProjectionMatrix();
	void setLookAt(glm::vec3 from, glm::vec3 to);
	const glm::mat4& getProjectionMatrix() const;

	virtual void update(struct GLFWwindow* window, float dt) {};

private:
	glm::mat4 m_worldTransform = glm::mat4(1);
	glm::mat4 m_projectionMatrix = glm::mat4(1);
	bool m_hasSetProjectionMatrix = false;
};
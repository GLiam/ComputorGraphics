#pragma warning( push )
#pragma warning( disable : 4201)
#pragma warning( disable : 4310)
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#pragma warning( pop )
#include "FirstPersonCamera.h"

void FirstPersonCamera::update(GLFWwindow* window, float dt)
{
	if (window == nullptr) return;

	auto& forward = getTransform()[2];
	auto& right = getTransform()[0];
	auto& up = getTransform()[1];

	auto worldUp = glm::vec4{ 0, 1, 0, 0 };

	//float moveSpeed = m_moveSpeed;
	//if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//{
	//	Translate(forward * deltaTime * moveSpeed);
	//}
	//if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//{
	//	Translate(forward * deltaTime * -moveSpeed);
	//}
	//if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//{
	//	Translate(right * deltaTime * moveSpeed);
	//}
	//if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//{
	//	Translate(right * deltaTime * -moveSpeed);
	//}
}

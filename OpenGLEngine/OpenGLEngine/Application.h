#pragma once
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include <Gizmos.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <imgui.h>
#include <iostream>

class Application
{
public:
	Application();
	virtual ~Application();

	virtual bool Startup() = 0;
	virtual void shutdown() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;

private:
	GLFWwindow * window = glfwCreateWindow(1280, 720, "REEEEEEEE Window", nullptr, nullptr);
};


#include "Application.h"
#include <chrono>

using glm::vec3;
using glm::vec4;
using glm::mat4;

int Application::run(std::string windowtitle, int windowWidth,
	int windowHeight, bool Fullscreen /*, std::string configFilePath = ""*/)
{
	auto succsessful = initalise(windowtitle, windowWidth, windowHeight, Fullscreen);
     
	if(!succsessful)
	{
		return -1;
	}

	if(!OnStartup())
	{
		Shutdown();
		return -2;
	}

	gameLoop();
	
	Shutdown();

	return 0;
}

void Application::Shutdown()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Application::initalise(std::string windowtitle, int windowWidth,
	int windowHeight, bool Fullscreen /*, std::string configFilePath = ""*/)
{
	if (glfwInit() == false)
		return false;
	
	auto monitor = glfwGetPrimaryMonitor();

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowtitle.c_str(), 
		(Fullscreen ? glfwGetPrimaryMonitor() : nullptr), nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);
	
	if (ogl_LoadFunctions() != ogl_LOAD_SUCCEEDED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

	m_window = window;
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;
	m_Fullscreen = Fullscreen;
	
	m_PreviousFrameTime = std::chrono::high_resolution_clock::now();

	return true;
}

void Application::gameLoop()
{
	while (m_isRunning)
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto timeTaken = now - m_PreviousFrameTime;
		m_dt = std::chrono::duration<float>(timeTaken).count();
		m_PreviousFrameTime = now;

		auto elapsedTime = now - m_apllicationStartTime;
		m_elapsedTime = std::chrono::duration<float>(elapsedTime).count();

		update();
		render();

		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}
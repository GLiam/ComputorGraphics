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


//	if (glfwInit() == false)
//		return -1;
//
//	
//	if (window == nullptr)
//	{
//		glfwTerminate();
//		return -2;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	if (ogl_LoadFunctions() != ogl_LOAD_SUCCEEDED)
//	{
//		glfwDestroyWindow(window);
//		glfwTerminate();
//		return -3;
//	}
//
//	aie::Gizmos::create(100, 10, 100, 10);
//
//	auto major = ogl_GetMajorVersion();
//	auto minor = ogl_GetMinorVersion();
//	std::cout << "GL: " << major << "." << minor << std::endl;
//}
//
//void Application::shutdown()
//{
//	aie::Gizmos::destroy();
//
//	glfwDestroyWindow(window);
//	glfwTerminate();
//}
//
//void Application::update()
//{
//	glfwSwapBuffers(window);
//	glfwPollEvents();
//
//
//	//return true;
//}
//
//void Application::draw()
//{
//
//
//	glClearColor(0.25f, 0.25f, 0.25f, 1);
//	glEnable(GL_DEPTH_TEST);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	aie::Gizmos::clear();
//	aie::Gizmos::addTransform(glm::mat4(1));
//
//	vec4 white(1);
//	vec4 black(0, 0, 0, 1);
//
//	for (int i = 0; i < 21; i++)
//	{
//		aie::Gizmos::addLine(vec3(-10 + i, 0, 10),
//			vec3(-10 + i, 0, -10),
//			i == 10 ? white : black);
//
//		aie::Gizmos::addLine(vec3(10, 0, -10 + i),
//			vec3(-10, 0, -10 + i),
//			i == 10 ? white : black);
//	}
//
//	aie::Gizmos::draw(projection * view);
//}


//int Application()
//{
//
//	while (glfwWindowShouldClose(window) == false &&
//		glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
//	{
//
//	}
//
//	//Do our Drawing 
//
//	return 0;
//}
#include "Application.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;

Application::Application()
{
}


Application::~Application()
{
}

bool Application::Startup()
{	
	if (glfwInit() == false)
		return -1;

	
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
		return -3;
	}

	aie::Gizmos::create(100, 10, 100, 10);

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	std::cout << "GL: " << major << "." << minor << std::endl;
}

void Application::shutdown()
{
	aie::Gizmos::destroy();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::update()
{
	glfwSwapBuffers(window);
	glfwPollEvents();


	//return true;
}

void Application::draw()
{
	mat4 view = glm::lookAt(vec3(10, 10, 10), vec3(0), vec3(0, 1, 0));
	mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);

	glClearColor(0.25f, 0.25f, 0.25f, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	aie::Gizmos::clear();
	aie::Gizmos::addTransform(glm::mat4(1));

	vec4 white(1);
	vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; i++)
	{
		aie::Gizmos::addLine(vec3(-10 + i, 0, 10),
			vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		aie::Gizmos::addLine(vec3(10, 0, -10 + i),
			vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	aie::Gizmos::draw(projection * view);
}


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
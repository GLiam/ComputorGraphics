#pragma warning( push )
#pragma warning( disable : 4201)
#pragma warning( disable : 4310)
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#pragma warning( pop )
#include "Application.h"
#include "Camera.h"
#include <iostream>
#include <Gizmos.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

class DemoApplication : public Application
{
public:
	virtual bool OnStartup() override
	{
		aie::Gizmos::create(10000, 10000, 10000, 10000);
		

		m_camera = new Camera();

		m_camera->setPosition({ 0, 0, 20, 1 });

		return true;
	}

	virtual void update() override
	{
		//Gizmos::clear();

		if (glfwWindowShouldClose(getWindow()))
		{
			setRunning(false);
		}

		//m_camera->Translate(m_camera.getTransform()[2] * getDeltaTime() * 5.0f);
		auto& CameraTransform = m_camera->getTransform();

		auto rot = glm::angleAxis(getDeltaTime(), glm::vec3{ 0, 1, 0 });
		CameraTransform *= glm::mat4_cast(rot);


		Gizmos::addTransform(mat4(1), 10.0f);
		Gizmos::addAABB({ 0, 0, 0 }, { 5, 5, 5 }, { 1, 0, 0, 1 });
	}

	virtual void render() override
	{
		mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);
		mat4 view = glm::lookAt(glm::vec3(20, 20, 20), vec3(0), vec3(0, 1, 0));

		Gizmos::draw(projection * view);
		//Gizmos::draw2D()
	}

	virtual void OnShutdown() override
	{
		delete m_camera;
		aie::Gizmos::destroy();
	}

private:
	Camera * m_camera;
};

int main()
{	
	//Application* theApp = new Application();
	//if (theApp->Startup() == true)
	//{
	//	while (theApp->update())
	//		theApp->draw();
	//	theApp->shutdown();

	//}

	//delete theApp;

	auto App = new DemoApplication();

	//App.run(1280, 720, "REEEEEEEE Window", nullptr, nullptr);

	App->setRunning(true);
	return App->run("REEEEEE", 1280, 720, false);

	delete App;
	return 0;
}
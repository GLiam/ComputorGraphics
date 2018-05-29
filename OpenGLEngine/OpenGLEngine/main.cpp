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
#include <Shader.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

class DemoApplication : public Application
{
public:
	bool OnStartup() override
	{
		
		aie::Gizmos::create(10000, 10000, 10000, 10000);
		m_camera = new Camera();
		m_camera->setPosition({ 0, 0, 20, 1 });

		m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
		m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
							getWindowWidth() / (float)getWindowHeight(),
							0.1f, 1000.0f);

		m_shader.loadShader(aie::eShaderStage::VERTEX,
								"./shader/simple.vert");
		m_shader.loadShader(aie::eShaderStage::FRAGMENT,
								"./shader/simple.frag");		
		if(m_shader.link() == false)
		{
			printf("Shader Error: %s\n", m_shader.getLastError());
			return false;
		}
		if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
		{
			printf("Bunny Mesh Error!\n");
			return false;
		}

		m_bunnyTransform = {
		20, 0, 0, 0,
		0, 20, 0, 0,
		0, 0, 20, 0,
		0, 0, 0, 20};

		Mesh::Vertex vertices[4];
		vertices[0].position = { -0.5f, 0, 0.5f, 1 };
		vertices[1].position = { 0.5f, 0, 0.5f, 1 };
		vertices[2].position = { -0.5f, 0, -0.5f, 1 };
		vertices[3].position = { 0.5f, 0, -0.5f, 1 };

		unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };

		m_quadMesh.initalise(4, vertices, 6, indices);
		//m_quadMesh.initaliseQuad();

		m_quadTransform = { 10, 0, 0, 0,
							0, 10, 0, 0,
							0, 0, 10, 0,
							0, 0, 0, 1 };

		return true;
	}

	void update() override
	{
		Gizmos::clear();

		if (glfwWindowShouldClose(getWindow()))
		{
			setRunning(false);
		}

		auto& CameraTransform = m_camera->getTransform();
		//m_camera->Translate(m_camera.getTransform()[2] * getDeltaTime() * 5.0f);

		auto rot = glm::angleAxis(getDeltaTime(), glm::vec3{ 0, 1, 0 });
		//CameraTransform *= rot;
		CameraTransform *= glm::mat4_cast(rot);

		Gizmos::addTransform(mat4(1), 10.0f);
		//Gizmos::addAABB({ 0, 0, 0 }, { 5, 5, 5 }, { 1, 0, 0, 1 });
	}

	void render() override
	{
		mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);
		mat4 view = glm::lookAt(glm::vec3(20, 20, 20), vec3(0), vec3(0, 1, 0));

		m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
									getWindowWidth() / (float)getWindowHeight(),
									0.1f, 1000.0f);

		m_shader.bind();

		auto pvm = m_projectionMatrix * m_viewMatrix * m_quadTransform;
		m_shader.bindUniform("ProjectionViewModel", pvm);


		m_bunnyMesh.draw();
		m_quadMesh.draw();
		
		Gizmos::draw(m_projectionMatrix * m_viewMatrix);

		glm::vec4 white(1);
		glm::vec4 black(0, 0, 0, 1);

		for (int i = 0; i < 21; i++)
		{
			aie::Gizmos::addLine(glm::vec3(-10 + i, 0, 10),
				glm::vec3(-10 + i, 0, -10),
				i == 10 ? white : black);

			aie::Gizmos::addLine(glm::vec3(10, 0, -10 + i),
				glm::vec3(-10, 0, -10 + i),
				i == 10 ? white : black);
		}


		Gizmos::draw(projection * view);
		Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
	}

	void OnShutdown() override
	{
		delete m_camera;
		aie::Gizmos::destroy();
	}

private:
	Camera * m_camera;
};

int main()
{	
	auto App = new DemoApplication();

	App->setRunning(true);

	int returnVal = App->run("REEEEEE", 1280, 720, false);


	delete App;
	return returnVal;
}
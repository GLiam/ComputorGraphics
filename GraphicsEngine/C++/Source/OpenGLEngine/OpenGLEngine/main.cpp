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
		glClearColor(0.25f, 0.25f, 0.25f, 1);

		glEnable(GL_DEPTH_TEST);

		aie::Gizmos::create(10000, 10000, 10000, 10000);
		m_camera = new Camera();
		m_camera->setPosition({ 0, 0, 50, 1 });

		m_viewMatrix = glm::lookAt(vec3(20), vec3(0), vec3(0, 1, 0));
		m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
							getWindowWidth() / (float)getWindowHeight(),
							0.1f, 1000.0f);

		//aie::Texture texture2;
		//texture1.load("numbered_gride.tga");
		aie::Texture texture1;
		texture1.load("soulspear_diffuse.tga");

		aie::Texture texture2;
		unsigned char texelData[4] = { 0, 255, 255, 0 };
		texture2.create(2, 2, aie::Texture::RED, texelData);

//****************************************************************************************//
		m_shader.loadShader(aie::eShaderStage::VERTEX,
								"./shader/simple.vert");
		m_shader.loadShader(aie::eShaderStage::FRAGMENT,
								"./shader/simple.frag");		

		m_PhongShader.loadShader(aie::eShaderStage::VERTEX,
								"./shader/Phong.vert");
		m_PhongShader.loadShader(aie::eShaderStage::FRAGMENT,
								"./shader/Phong.frag");

		m_TexturedShader.loadShader(aie::eShaderStage::VERTEX,
								"./shader/texture.vert");
		m_TexturedShader.loadShader(aie::eShaderStage::FRAGMENT,
								"./shader/texture.frag");
		
		m_TexturedShader.loadShader(aie::eShaderStage::VERTEX,
								"./shader/texture.vert");
		m_TexturedShader.loadShader(aie::eShaderStage::FRAGMENT,
								"./shader/texture.frag");

//****************************************************************************************//
		if(m_shader.link() == false)
		{
			printf("Shader Error: %s\n", m_shader.getLastError());
			return false;
		}
		if (m_PhongShader.link() == false)
		{
			printf("PhongShader Error: %s\n", m_PhongShader.getLastError());
			return false;
		}
		if (m_TexturedShader.link() == false)
		{
			printf("TexturedShader Error: %s\n", m_TexturedShader.getLastError());
			return false;
		}
		if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
		{
			printf("Bunny Mesh Error!\n");
			return false;
		}
		if (m_DragonMesh.load("./stanford/Dragon.obj") == false)
		{
			printf("Dragon Mesh Error!\n");
			return false;
		}
		if (m_lucyMesh.load("./stanford/Lucy.obj") == false)
		{
			printf("Lucy Mesh Error!\n");
			return false;
		}
		if (m_gridTexture.load("./shader/numbered_grid.tga") == false)
		{
			printf("Failed to load texture!\n");
			return false;
		}
		if(m_spearMesh.load("./stanford/soulspear.obj", true, true) == false)
		{
			printf("Soulspear Mesh Error!\n");
			return false;
		}

//********************************************************************************************//
		m_spearTransform = { 1, 0, 0, 0,
							 0, 1, 0, 0,
							 0, 0, 1, 0,
							 6, 0, -6, 1 };

		//m_bunnyTransform = mat4(1);
		//m_bunnyTransform[3] = vec4(1, 0, 0, 1);

		m_bunnyTransform = { 0.5f, 0, 0, 0,
							 0, 0.5f, 0, 0,
							 0, 0, 0.5f, 0,
							 6, 0, 0, 1 };

		m_DragonTransform = { 0.5f, 0, 0, 0,
							  0, 0.5f, 0, 0,
							  0, 0, 0.5f, 0,
							  -6, 0, 0, 1 };

		m_lucyTransform = { 0.5f, 0, 0, 0,
							0, 0.5f, 0, 0,
							0, 0, 0.5f, 0,
							-4, 0, -6, 1 };

		//Mesh::Vertex vertices[4];
		//vertices[0].position = { -0.5f, 0, 0.5f, 1 };
		//vertices[0].texCoord = { 0.0f, 0.0f };
		//vertices[1].position = { 0.5f, 0, 0.5f, 1 };
		//vertices[1].texCoord = { 1.0f, 0.0f };
		//vertices[2].position = { -0.5f, 0, -0.5f, 1 };
		//vertices[2].texCoord = { 1.0f, 1.0f };
		//vertices[3].position = { 0.5f, 0, -0.5f, 1 };
		//vertices[3].texCoord = { 0.0f, 1.0f };
		//unsigned int indices[6] = { 0, 1, 2, 2, 1, 3 };
		//m_quadMesh.initalise(4, vertices, 6, indices);
		m_quadMesh.initaliseQuad();

		m_quadTransform = { 20, 0, 0, 0,
							0, 20, 0, 0,
							0, 0, 20, 0,
							0, 0, 0, 1 };

//********************************************************************************************//

		m_light.diffuse = { 10, 0.8f, 5};
		m_secondLight.diffuse = { 10, 5, 0.9f };
		m_thirdLight.diffuse = { 0.8f, 0, 5 };

		m_light.specular = { 1, 0, 0 };
		m_secondLight.specular = { 0, 1, 0 };
		m_thirdLight.specular = { 0, 0, 1 };

		m_ambientLight = { 0.25f, 0.25f, 0.25f };

//********************************************************************************************//

		return true;
	}

	void update() override
	{
		Gizmos::clear();


		if (glfwWindowShouldClose(getWindow()))
		{
			setRunning(false);
		}
		
		float time = glfwGetTime();

		m_light.direction = glm::normalize(vec3(glm::cos(time * 8), glm::sin(time * 16), 0));
		m_secondLight.direction = glm::normalize(vec3(glm::cos(time * 16), glm::sin(time * 8), 0));
		m_thirdLight.direction = glm::normalize(vec3(glm::cos(time * -16), glm::sin(time * -2), 0));

		auto& CameraTransform = m_camera->getTransform();
		//m_camera->Translate(m_camera.getTransform()[2] * getDeltaTime() * 5.0f);

		auto rot = glm::angleAxis(getDeltaTime(), glm::vec3{ 0, 1, 0 });
		//CameraTransform *= rot;
		CameraTransform *= glm::mat4_cast(rot);

		//Gizmos::addTransform(mat4(1), 10.0f);
		//Gizmos::addAABB({ 0, 0, 0 }, { 5, 5, 5 }, { 1, 0, 0, 1 });
	}

	void render() override
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 projection = glm::perspective(glm::pi<float>() * 0.25f, 16 / 9.0f, 0.1f, 1000.0f);
		mat4 view = glm::lookAt(glm::vec3(20, 20, 20), vec3(0), vec3(0, 1, 0));

		m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
									getWindowWidth() / (float)getWindowHeight(),
									0.1f, 1000.0f);
		
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

//*********************************************************************************************************//

		auto pvmSpear = m_projectionMatrix * m_viewMatrix * m_spearTransform;
		auto pvmBunny = m_projectionMatrix * m_viewMatrix * m_bunnyTransform;
		auto pvmDragon = m_projectionMatrix * m_viewMatrix * m_DragonTransform;
		auto pvmLucy = m_projectionMatrix * m_viewMatrix * m_lucyTransform;
		auto pvmGrid = m_projectionMatrix * m_viewMatrix * m_quadTransform;
		//auto pvmQuad = m_projectionMatrix * m_viewMatrix * m_quadTransform;

//********************************************************************************************************//
		m_TexturedShader.bind();
		m_TexturedShader.bindUniform("ProjectionViewModel", pvmSpear);
		m_TexturedShader.bindUniform("diffuseTexture", 0);		
		m_spearMesh.draw();
		
//********************************************************************************************************//

		m_TexturedShader.bindUniform("ProjectionViewModel", pvmGrid);
		m_TexturedShader.bindUniform("diffuseTexture", 0);
		m_gridTexture.bind(0);
		m_quadMesh.draw();

//********************************************************************************************************//
		//m_spearMesh.draw();
		//m_shader.bind();
		m_PhongShader.bind();
			
		//m_shader.bindUniform("ProjectionViewModel", ovm);

		m_PhongShader.bindUniform("cameraPosition", m_camera->getPosition());

//*******************************************************************************************************//
		m_PhongShader.bindUniform("specularPower", 1);

		m_PhongShader.bindUniform("ProjectionViewModel", pvmBunny);
	
		//ambient light colour
		m_PhongShader.bindUniform("Ia", m_ambientLight);
		//diffuse light colour
		m_PhongShader.bindUniform("Id", m_light.diffuse);
		//specular light colour
		m_PhongShader.bindUniform("Is", m_light.specular);
		m_PhongShader.bindUniform("LightDirection", m_light.direction);
		
		m_PhongShader.bindUniform("Id2", m_thirdLight.diffuse);
		m_PhongShader.bindUniform("Is2", m_thirdLight.specular);
		m_PhongShader.bindUniform("LightDirection2", m_thirdLight.direction);
		
		m_PhongShader.bindUniform("ProjectionViewModel", pvmBunny);
		m_PhongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_bunnyTransform)));		
		m_bunnyMesh.draw();

//******************************************************************************************************//

		m_PhongShader.bindUniform("ProjectionViewModel", pvmLucy);

		//ambient light colour
		m_PhongShader.bindUniform("Ia", m_ambientLight);
		//diffuse light colour
		m_PhongShader.bindUniform("Id", m_light.diffuse);
		m_PhongShader.bindUniform("Id", m_secondLight.diffuse);
		m_PhongShader.bindUniform("Id", m_thirdLight.diffuse);
		//specular light colour
		m_PhongShader.bindUniform("Is", m_light.specular);
		m_PhongShader.bindUniform("Is", m_secondLight.specular);
		m_PhongShader.bindUniform("Is", m_thirdLight.specular);

		m_PhongShader.bindUniform("LightDirection", m_light.direction);
		m_PhongShader.bindUniform("LightDirection", m_secondLight.direction);
		m_PhongShader.bindUniform("LightDirection", m_thirdLight.direction);

		//m_PhongShader.bindUniform("Id2", m_light.diffuse);
		//m_PhongShader.bindUniform("Is2", m_light.specular);
		//m_PhongShader.bindUniform("LightDirection2", m_light.direction);

		m_PhongShader.bindUniform("ProjectionViewModel", pvmLucy);
		m_PhongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_lucyTransform)));
		m_lucyMesh.draw();

//*****************************************************************************************************//

		//m_PhongShader.bindUniform("ProjectionViewModel", pvmBunny);
		////ambient light colour
		////diffuse light colour
		////specular light colour
		//m_PhongShader.bindUniform("ProjectionViewModel", pvmBunny);
		//m_PhongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_bunnyTransform)));
		//m_bunnyMesh.draw();

//*****************************************************************************************************//
		m_PhongShader.bindUniform("specularPower", 2);

		m_PhongShader.bindUniform("ProjectionViewModel", pvmDragon);

		//ambient light colour
		m_PhongShader.bindUniform("Ia", m_ambientLight);
		//diffuse light colour
		m_PhongShader.bindUniform("Id", m_secondLight.diffuse);
		//specular light colour
		m_PhongShader.bindUniform("Is", m_secondLight.specular);

		m_PhongShader.bindUniform("LightDirection", m_secondLight.direction);

		m_PhongShader.bindUniform("ProjectionViewModel", pvmDragon);
		m_PhongShader.bindUniform("NormalMatrix", glm::inverseTranspose(glm::mat3(m_DragonTransform)));
		m_DragonMesh.draw();

//******************************************************************************************************//

		//Gizmos::draw(projection * view);
		//Gizmos::draw2D((float)getWindowWidth(), (float)getWindowHeight());
		Gizmos::draw(m_projectionMatrix * m_viewMatrix);
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

	int returnVal = App->run("Graphics Engine", 1280, 720, false);


	delete App;
	return returnVal;
}
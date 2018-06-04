#pragma once
#pragma warning( push )
#pragma warning( disable : 4201)
#pragma warning( disable : 4310)
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#pragma warning( pop )
#include <Gizmos.h>
#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include <imgui.h>
#include <iostream>
#include <chrono>
#include <Shader.h>
#include "Mesh.h"
#include <OBJMesh.h>

class Application
{
public:

	virtual bool OnStartup() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void OnShutdown() = 0;

	int run(std::string windowtitle, int windowWidth,
		int windowHeight, bool Fullscreen /*, std::string configFilePath = ""*/);

	bool initalise(std::string windowtitle, int windowWidth,
		int windowHeight, bool Fullscreen /*, std::string configFilePath*/);

	void gameLoop();

	void Shutdown();

	GLFWwindow* getWindow() const { return m_window; }
	
	int getWindowWidth() const { return m_windowWidth; }
	int getWindowHeight() const { return m_windowHeight; }
	bool getFullscreen() const { return m_Fullscreen; }

	bool getRunning() const { return m_isRunning; }
	void setRunning(bool value) { m_isRunning = value; }

	float getDeltaTime() const { return m_dt; }
	float getElapsedTime() const { return m_elapsedTime; }

protected:
	glm::mat4			m_viewMatrix;
	glm::mat4			m_projectionMatrix;

	aie::OBJMesh		m_bunnyMesh;
	glm::mat4			m_bunnyTransform;
	
	aie::ShaderProgram	m_shader;
	aie::ShaderProgram	m_PhongShader;

	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform; 

	struct Light
	{
		glm::vec3 direction;
	};

	Light				m_light;

private:
	GLFWwindow * m_window;
	
	int m_windowWidth;
	int m_windowHeight;
	
	bool m_Fullscreen;
	bool m_isRunning;

	float m_dt = 0;
	float m_elapsedTime = 0;
	
	std::chrono::high_resolution_clock::time_point m_PreviousFrameTime;
	std::chrono::high_resolution_clock::time_point m_apllicationStartTime;
};
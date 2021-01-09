#include "External/filesystem.h"

#include "Scene.h"

#pragma once
class Window {
private:
	void initializeGLFW();
	void createWindow();
	void initShader();
	void initScene();
	void processInput(GLFWwindow* window);
	void runWindow();

	GLFWwindow* mainWindow;
	int width;
	int height;
	Scene* scene;
	Shader shader;

	//Textures
	unsigned int albedo;
	unsigned int normal;
	unsigned int metallic;
	unsigned int roughness;
	unsigned int ao;

public:
	Window() {}

	int initWindow(int width, int height);
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};
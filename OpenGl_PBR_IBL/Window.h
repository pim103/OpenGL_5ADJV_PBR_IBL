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

	Shader pbrShader;
	Shader equirectangularToCubemapShader;
	Shader irradianceShader;
	Shader prefilterShader;
	Shader brdfShader;
	Shader backgroundShader;

public:
	Window() {}

	int initWindow(int width, int height);
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};
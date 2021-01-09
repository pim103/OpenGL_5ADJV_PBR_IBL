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

public:
	Window() {}

	int initWindow(int width, int height);
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};
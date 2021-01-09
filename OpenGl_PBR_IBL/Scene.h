#include <iostream>
#include <vector>
using namespace std;

#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "External/camera.h"
#include "External/shader.h"

#pragma once
class Scene {
private:
	void initLights();
	void initCamera();
	void renderSphere();

	Shader shader;

	int nbSpherePerLine;
	int nbSpherePerColumn;
	int width;
	int height;
	float spacing;

	vector<glm::vec3> lightPositions;
	vector<glm::vec3> lightColors;

	unsigned int sphereVAO;
	unsigned int indexCount;

	//Textures
	unsigned int albedo;
	unsigned int normal;
	unsigned int metallic;
	unsigned int roughness;
	unsigned int ao;

public:
	Scene() {}
	Scene(int width, int height);
	Scene(int width, int height, Shader shader);

	void initScene();
	void renderScene();
	void Scene::setSphereMaterial(unsigned int albedo, unsigned int normal, unsigned int metallic, unsigned int roughness, unsigned int ao);
};
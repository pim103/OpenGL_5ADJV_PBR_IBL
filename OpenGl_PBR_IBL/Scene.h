#include <iostream>
#include <vector>
using namespace std;

#include "Sphere.h"

#include "External/camera.h"
#include "External/shader.h"

#pragma once
class Scene {
private:
	void initLights();
	void initCamera();
	void renderSphere();
	void initSpheres();

	Shader shader;

	int nbSpherePerLine;
	int nbSpherePerColumn;
	int width;
	int height;
	float spacing;

	vector<glm::vec3> lightPositions;
	vector<glm::vec3> lightColors;
	vector<Sphere*> spheres;

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
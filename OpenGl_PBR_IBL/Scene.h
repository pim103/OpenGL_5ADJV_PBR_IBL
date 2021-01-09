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
	void initSpheres();
	void initBuffer();

	int nbSpherePerLine;
	int nbSpherePerColumn;
	int width;
	int height;
	float spacing;

	vector<glm::vec3> lightPositions;
	vector<glm::vec3> lightColors;
	vector<Sphere*> spheres;
	vector<Sphere*> spheresLight;

	Shader pbrShader;
	Shader equirectangularToCubemapShader;
	Shader irradianceShader;
	Shader prefilterShader;
	Shader brdfShader;
	Shader backgroundShader;

	MaterialList materialList;
	unsigned int envCubemap;
	unsigned int irradianceMap;
	unsigned int prefilterMap;
	unsigned int brdfLUTTexture;

public:
	Scene(int width, int height);

	void initScene();
	void renderScene();
	void setShaders(Shader pbrShader, Shader equirectangularToCubemapShader, Shader irradianceShader, Shader prefilterShader, Shader brdfShader, Shader backgroundShader);
};
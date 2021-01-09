#include <iostream>
#include <vector>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

using namespace std;

#include "External/filesystem.h"

class Material {
public:
	Material() {}
	Material(unsigned int albedo, unsigned int normal, unsigned int metallic, unsigned int roughness, unsigned int ao);

	unsigned int albedo;
	unsigned int normal;
	unsigned int metallic;
	unsigned int roughness;
	unsigned int ao;
};

class MaterialList {
private:
public:
	void initMaterials();

	Material metal_tile;
	Material stone_and_grass;
};
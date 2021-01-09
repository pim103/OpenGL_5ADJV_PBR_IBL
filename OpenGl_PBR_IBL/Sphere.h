#include "Material.h"

class Sphere {
private:
	Material material;
	glm::vec3 position;

public:
	Sphere(Material mat, glm::vec3 position);
	
	void bindMaterial();
	void renderSphere();
	glm::vec3 getPosition();
};
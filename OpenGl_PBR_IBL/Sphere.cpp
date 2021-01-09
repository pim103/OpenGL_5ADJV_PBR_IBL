#include "Sphere.h"

Sphere::Sphere(Material mat, glm::vec3 pos) {
	material = mat;
    position = pos;
}

void Sphere::bindMaterial() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, material.albedo);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, material.normal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, material.metallic);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, material.roughness);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, material.ao);
}

glm::vec3 Sphere::getPosition() {
    return position;
}
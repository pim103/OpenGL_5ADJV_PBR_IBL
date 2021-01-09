#include "Material.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

unsigned int loadTexture(char const* path);

Material::Material(unsigned int albedo, unsigned int normal, unsigned int metallic, unsigned int roughness, unsigned int ao) {
	this->albedo = albedo;
	this->normal = normal;
	this->metallic = metallic;
	this->roughness = roughness;
	this->ao = ao;
}

void MaterialList::initMaterials() {
	unsigned int albedo = loadTexture(FileSystem::getPath("data/textures/metal_tiles/Metal_Tiles_003_basecolor.jpg").c_str());
	unsigned int normal = loadTexture(FileSystem::getPath("data/textures/metal_tiles/Metal_Tiles_003_normal.jpg").c_str());
	unsigned int metallic = loadTexture(FileSystem::getPath("data/textures/metal_tiles/Metal_Tiles_003_metallic.jpg").c_str());
	unsigned int roughness = loadTexture(FileSystem::getPath("data/textures/metal_tiles/Metal_Tiles_003_roughness.jpg").c_str());
	unsigned int ao = loadTexture(FileSystem::getPath("data/textures/metal_tiles/Metal_Tiles_003_ambientOcclusion.jpg").c_str());

	metal_tile = Material(albedo, normal, metallic, roughness, ao);

	albedo = loadTexture(FileSystem::getPath("data/textures/stoneWithGrass/Stone_Path_006_basecolor.jpg").c_str());
	normal = loadTexture(FileSystem::getPath("data/textures/stoneWithGrass/Stone_Path_006_normal.jpg").c_str());
	metallic = loadTexture(FileSystem::getPath("data/textures/stoneWithGrass/Stone_Path_006_height.png").c_str());
	//roughness = loadTexture(FileSystem::getPath("data/textures/stoneWithGrass/Stone_Path_006_roughness.jpg").c_str());
	ao = loadTexture(FileSystem::getPath("data/textures/stoneWithGrass/Stone_Path_006_ambientOcclusion.jpg").c_str());

    stone_and_grass = Material(albedo, normal, metallic, roughness, ao);
}

unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

unsigned int MaterialList::loadEnvMap() {
    // pbr: load the HDR environment map
    // ---------------------------------
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    float* data = stbi_loadf(FileSystem::getPath("data/textures/misty_pines_1k.hdr").c_str(), &width, &height, &nrComponents, 0);
    unsigned int hdrTexture;
    if (data)
    {
        glGenTextures(1, &hdrTexture);
        glBindTexture(GL_TEXTURE_2D, hdrTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data); // note how we specify the texture's data value to be float

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Failed to load HDR image." << std::endl;
    }

    return hdrTexture;
}
#include "Scene.h"

Camera globalCamera;

Scene::Scene(int width, int height) {
    nbSpherePerLine = 7;
    nbSpherePerColumn = 7;
    spacing = 2.5f;
    sphereVAO = 0;

    this->width = width;
    this->height = height;
}

Scene::Scene(int width, int height, Shader shader) {
    this->shader = shader;
    nbSpherePerLine = 7;
    nbSpherePerColumn = 7;
    spacing = 2.5f;
    sphereVAO = 0;

    this->width = width;
    this->height = height;
}

void Scene::initScene() {
	initLights();
    initCamera();
    initSpheres();
}

void Scene::initSpheres() {
    MaterialList materialList;
    materialList.initMaterials();

    for (int row = 0; row < nbSpherePerLine; ++row)
    {
        for (int col = 0; col < nbSpherePerColumn; ++col)
        {
            Material mat = col % 2 == 0 ? materialList.metal_tile : materialList.stone_and_grass;

            spheres.push_back(new Sphere(mat, glm::vec3(
                (float)(col - (nbSpherePerColumn / 2)) * spacing,
                (float)(row - (nbSpherePerLine / 2)) * spacing,
                0.0f
            )));
        }
    }
}

void Scene::initLights() {
    lightPositions.push_back(glm::vec3(0.0f, 0.0f, 10.0f));

    lightColors.push_back(glm::vec3(300.0f, 300.0f, 300.0f));

    glm::mat4 projection = glm::perspective(glm::radians(globalCamera.Zoom), (float)width / (float)height, 0.1f, 100.0f);
    shader.use();
    shader.setMat4("projection", projection);
}

void Scene::initCamera() {
    globalCamera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
}

void Scene::renderScene() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    glm::mat4 view = globalCamera.GetViewMatrix();
    shader.setMat4("view", view);
    shader.setVec3("camPos", globalCamera.Position);

    glm::mat4 model = glm::mat4(1.0f);

    int nbSphere = spheres.size();
    for (int idxSphere = 0; idxSphere < nbSphere; ++idxSphere) {
        spheres[idxSphere]->bindMaterial();
        model = glm::mat4(1.0f);
        model = glm::translate(model, spheres[idxSphere]->getPosition());
        shader.setMat4("model", model);
        renderSphere();
    }

    for (int row = 0; row < nbSpherePerLine; ++row)
    {
        for (int col = 0; col < nbSpherePerColumn; ++col)
        {
        }
    }

    int nbLights = lightPositions.size();
    for (unsigned int i = 0; i < nbLights; ++i)
    {
        glm::vec3 newPos = lightPositions[i] + glm::vec3(sin(glfwGetTime() * 5.0) * 5.0, 0.0, 0.0);
        newPos = lightPositions[i];
        shader.setVec3("lightPositions[" + std::to_string(i) + "]", newPos);
        shader.setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);

        model = glm::mat4(1.0f);
        model = glm::translate(model, newPos);
        model = glm::scale(model, glm::vec3(0.5f));
        shader.setMat4("model", model);
        renderSphere();
    }
}

void Scene::renderSphere() {
    if (sphereVAO == 0)
    {
        glGenVertexArrays(1, &sphereVAO);

        unsigned int vbo, ebo;
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;

        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359;
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions.push_back(glm::vec3(xPos, yPos, zPos));
                uv.push_back(glm::vec2(xSegment, ySegment));
                normals.push_back(glm::vec3(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    indices.push_back(y * (X_SEGMENTS + 1) + x);
                }
            }
            oddRow = !oddRow;
        }
        indexCount = indices.size();

        std::vector<float> data;
        for (size_t i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x);
            data.push_back(positions[i].y);
            data.push_back(positions[i].z);
            if (uv.size() > 0)
            {
                data.push_back(uv[i].x);
                data.push_back(uv[i].y);
            }
            if (normals.size() > 0)
            {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
        }
        glBindVertexArray(sphereVAO);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        float stride = (3 + 2 + 3) * sizeof(float);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
    }

    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}
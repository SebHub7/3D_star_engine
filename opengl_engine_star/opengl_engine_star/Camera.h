#pragma once
#include <glm/vec3.hpp>
#include <GLFW/glfw3.h>
#include <glm/detail/func_geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:
	glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up_vector;
    float fov;
    float near_z, far_z;
    const float cameraSpeed = 0.005;

public:
    Camera();

    Camera(float fov, float near_z, float far_z);

    void lookAt(glm::vec3 target);

    glm::mat4 getViewMatrix();

    glm::mat4 getPerspectiveProjectionMatrix(unsigned int WINDOW_WIDTH, unsigned int WINDOW_HEIGHT) const;

    void processInput(GLFWwindow* window);
};
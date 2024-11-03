#include "Camera.h"

Camera::Camera()
{
    position = glm::vec3(0.0, 0.0, 0.0);
    direction = glm::vec3(0.0, 0.0, -1.0);
    up_vector = glm::vec3(0.0, 1.0, 0.0);
    fov = 45.0f;
    near_z = 0.1f;
    far_z = 1000.0f;
}

Camera::Camera(float fov, float near_z, float far_z)
{
    position = glm::vec3(0.0, 0.0, 0.0);
    direction = glm::vec3(0.0, 0.0, -1.0);
    up_vector = glm::vec3(0.0, 1.0, 0.0);
    this->fov = fov;
    this->near_z = near_z;
    this->far_z = far_z;
}

void Camera::lookAt(glm::vec3 target)
{
    direction = glm::normalize(target - position);
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + direction, up_vector);
}

glm::mat4 Camera::getPerspectiveProjectionMatrix(unsigned int WINDOW_WIDTH, unsigned int WINDOW_HEIGHT) const
{
    return glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, near_z, far_z);
}

void Camera::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += cameraSpeed * direction;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= cameraSpeed * direction;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(direction, up_vector)) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(direction, up_vector)) * cameraSpeed;
}
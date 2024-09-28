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

public:

	Camera()
	{
		position = glm::vec3(0.0, 0.0, 0.0);
		direction = glm::vec3(0.0, 0.0, -1.0);
		up_vector = glm::vec3(0.0, 1.0, 0.0);
	}

    glm::mat4 getViewMatrix() const
    {
        return glm::lookAt(position, position + direction, up_vector);
    }

    void processInput(GLFWwindow* window)
    {
        const float cameraSpeed = 0.01;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += cameraSpeed * direction;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= cameraSpeed * direction;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= glm::normalize(glm::cross(direction, up_vector)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
           position += glm::normalize(glm::cross(direction, up_vector)) * cameraSpeed;
    }
};
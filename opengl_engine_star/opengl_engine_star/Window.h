#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Renderer.h"
#include "Camera.h"
#include "Mesh.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

struct Window
{
	int WINDOW_WIDTH, WINDOW_HEIGHT;
	GLFWwindow* window;

	Window()
	{
		WINDOW_WIDTH = 800;
		WINDOW_HEIGHT = 600;
		initWindow();
	}

	~Window()
	{
		glfwTerminate();
	}

	int initWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "3D Star engine", NULL, NULL);

		if (window == NULL)
		{
			printf("Failed to create GLFW window\n");
			glfwTerminate();
			return -1;
		}
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			printf("Failed to initialize GLAD\n");
			return -1;
		}

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	}


	void run(Renderer& r, Camera& cam, Mesh& m)
	{
		while (!glfwWindowShouldClose(window))
		{
			cam.processInput(window);
			r.draw(cam, m.vao, m.vertices.size());

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
};
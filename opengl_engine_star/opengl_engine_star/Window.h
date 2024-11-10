#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Renderer.h"
#include "Camera.h"
#include "Mesh.h"

struct Window
{
	int WINDOW_WIDTH, WINDOW_HEIGHT;
	GLFWwindow* window;

	Window();
	~Window();

	int initWindow();

	void run(Renderer& r, Camera& cam, Mesh& m);
};
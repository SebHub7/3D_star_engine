#pragma once
#include "Shader.h"
#include "Camera.h"

class Renderer
{
private:
	Shader shader;
	int WINDOW_WIDTH, WINDOW_HEIGHT;

public:

	Renderer(int WINDOW_WIDTH, int WINDOW_HEIGHT);

	void draw(Camera& cam, GLuint& vao, int vertices_size) const;
};
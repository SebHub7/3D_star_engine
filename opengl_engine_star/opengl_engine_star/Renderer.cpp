#include "Renderer.h"

Renderer::Renderer(int WINDOW_WIDTH, int WINDOW_HEIGHT)
{
	this->WINDOW_WIDTH = WINDOW_WIDTH;
	this->WINDOW_HEIGHT = WINDOW_HEIGHT;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//cam.lookAt(m.getObjectCenter());
	shader.compileShader("vertex_shader.glsl", "fragment_shader.glsl");
}


void Renderer::draw(Camera& cam, GLuint& vao, int vertices_size) const
{
	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao);
	glUseProgram(shader.program);

	glm::mat4 view = cam.getViewMatrix();
	glm::mat4 projection = cam.getPerspectiveProjectionMatrix(WINDOW_WIDTH, WINDOW_HEIGHT);
	glm::mat4 vp_matrix = projection * view;

	glUniformMatrix4fv(glGetUniformLocation(shader.program, "vp"), 1, GL_FALSE, &vp_matrix[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, vertices_size);
}
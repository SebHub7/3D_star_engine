#pragma once
#include <vector>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <fstream>
#include <iostream>

struct Mesh
{
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texture_coordinates;
	std::vector<glm::vec3> normals;

	std::vector<unsigned int> indices_vertices;

	bool has_normals = false;
	bool has_texture_coordinates = false;
	bool has_material = false;

	GLuint vao;
	GLuint vbo_vertices;
	GLuint vbo_texture_coordinates;
	GLuint vbo_normals;

	Mesh();

	~Mesh();

	void initBuffers();

	unsigned int getVerticesByteSize();

	unsigned int getTextureCoordinatesByteSize();

	unsigned int getNormalsByteSize();

	glm::vec3 getObjectCenter()
	{
		glm::vec3 p_min(9999, 9999, 9999);
		glm::vec3 p_max(-9999, -9999, -9999);

		for (glm::vec3& v : vertices)
		{
			if (v.x < p_min.x)
				p_min.x = v.x;
			if (v.y < p_min.y)
				p_min.y = v.y;
			if (v.z < p_min.z)
				p_min.z = v.z;

			if (v.x > p_max.x)
				p_max.x = v.x;
			if (v.y > p_max.y)
				p_max.y = v.y;
			if (v.z > p_max.z)
				p_max.z = v.z;
		}
		return (p_min + p_max) / 2.0f;
	}
};

// duplique les sommets, coordonnées de textures et normales
Mesh read_obj(std::string file_name);



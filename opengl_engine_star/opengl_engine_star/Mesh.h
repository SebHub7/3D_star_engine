#pragma once
#include <vector>
#include <glm/vec3.hpp>
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

	GLuint vao;
	GLuint vbo_vertices;
	GLuint vbo_texture_coordinates;
	GLuint vbo_normals;

	Mesh(){}

	~Mesh()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo_vertices);
		glDeleteBuffers(1, &vbo_texture_coordinates);
		glDeleteBuffers(1, &vbo_normals);
	}

	void initBuffers()
	{
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front().x, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		if (has_texture_coordinates)
		{
			glGenBuffers(1, &vbo_texture_coordinates);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_texture_coordinates);
			glBufferData(GL_ARRAY_BUFFER, texture_coordinates.size() * sizeof(glm::vec2), &texture_coordinates.front().x, GL_STATIC_DRAW);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);
		}

		if (has_normals)
		{
			glGenBuffers(1, &vbo_normals);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front().x, GL_STATIC_DRAW);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(2);
		}
	}

	unsigned int getVerticesByteSize()
	{
		return vertices.size() * sizeof(glm::vec3);
	}

	unsigned int getTextureCoordinatesByteSize()
	{
		return texture_coordinates.size() * sizeof(glm::vec2);
	}

	unsigned int getNormalsByteSize()
	{
		return normals.size() * sizeof(glm::vec3);
	}

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
Mesh read_obj(std::string file_name)
{
	Mesh m;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> texture_coordinates;
	std::vector<glm::vec3> normals;
	std::string line;
	std::ifstream file(file_name);

	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			float x, y, z;

			if (line[0] == 'v')
			{
				if (line[1] == ' ')
				{
					sscanf_s(line.c_str(), "v %f %f %f", &x, &y, &z);
					vertices.push_back(glm::vec3(x, y, z));
				}
				else if (line[1] == 't')
				{
					sscanf_s(line.c_str(), "vt %f %f", &x, &y);
					texture_coordinates.push_back(glm::vec2(x, y));
				}
				else if (line[1] == 'n')
				{
					sscanf_s(line.c_str(), "vn %f %f %f", &x, &y, &z);
					normals.push_back(glm::vec3(x, y, z));
				}
			}

			else if(line[0] == 'f')
			{
				int more_data;
				const char* string = line.c_str();
				std::vector<int> indices_v;
				std::vector<int> indices_vt;
				std::vector<int> indices_vn;

				for (string = string + 1;; string += more_data)
				{
					more_data = 0;
					indices_v.push_back(0); // indices non valide
					indices_vt.push_back(0);
					indices_vn.push_back(0);

					if (sscanf_s(string, " %d/%d/%d %n", &indices_v.back(), &indices_vt.back(), &indices_vn.back(), &more_data) == 3)
						continue;
					else if (sscanf_s(string, " %d//%d %n", &indices_v.back(), &indices_vn.back(), &more_data) == 2)
						continue;
					else if (sscanf_s(string, " %d/%d %n", &indices_v.back(), &indices_vt.back(), &more_data) == 2)
						continue;
					else if (sscanf_s(string, " %d% n", &indices_v.back(), &more_data) == 1)
						continue;
					else if (more_data == 0)
					{
						indices_v.pop_back();
						indices_vt.pop_back();
						indices_vn.pop_back();
						break;
					}
				}

				// création des sommets, textures_coord et normales des triangles
				for (int i = 0; i < indices_v.size() - 2; i++)
				{
					m.vertices.push_back(vertices[indices_v[0] -1]);
					m.vertices.push_back(vertices[indices_v[i+1] -1]);
					m.vertices.push_back(vertices[indices_v[i+2] -1]);

					if (indices_vt.size() > 0)
					{
						m.texture_coordinates.push_back(texture_coordinates[indices_vt[0] - 1]);
						m.texture_coordinates.push_back(texture_coordinates[indices_vt[i+1] - 1]);
						m.texture_coordinates.push_back(texture_coordinates[indices_vt[i+2] - 1]);
					}

					if (indices_vn.size() > 0)
					{
						m.normals.push_back(normals[indices_vn[0] - 1]);
						m.normals.push_back(normals[indices_vn[i+1] - 1]);
						m.normals.push_back(normals[indices_vn[i+2] - 1]);
					}
				}
			}
		}
		if (texture_coordinates.size() > 0)
			m.has_texture_coordinates = true;

		if (normals.size() > 0)
			m.has_normals = true;

		file.close();
	}
	return m;
}
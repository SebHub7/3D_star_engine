#pragma once
#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

struct Shader
{	
    GLuint program;

	Shader() : program(0)
    {}

    std::string getFileContent(std::string file_name)
    {
        std::ifstream file(file_name);
        std::string content;

        if (file)
        {
            std::ostringstream ss;
            ss << file.rdbuf(); // reading data
            content = ss.str();
        }
        return content;
    }

	unsigned int& compileVertexShader(std::string file_name)
	{
        unsigned int vertex_program;

        std::string content_str = getFileContent(file_name);
        const char * content = content_str.c_str();

        vertex_program = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_program, 1, &content, NULL);
        glCompileShader(vertex_program);

        int  success;
        char infoLog[512];
        glGetShaderiv(vertex_program, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(vertex_program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        return vertex_program;
	}

    unsigned int& compileFragmentShader(std::string file_name)
    {
        unsigned int fragment_program;

        std::string content_str = getFileContent(file_name);
        const char* content = content_str.c_str();

        fragment_program = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_program, 1, &content, NULL);
        glCompileShader(fragment_program);

        int  success;
        char infoLog[512];
        glGetShaderiv(fragment_program, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(fragment_program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        return fragment_program;
    }

    void compileShader(std::string vertex_file, std::string fragment_file)
    {
        unsigned int vertex_program = compileVertexShader(vertex_file);
        unsigned int fragment_program = compileFragmentShader(fragment_file);

        program = glCreateProgram();

        glAttachShader(program, vertex_program);
        glAttachShader(program, fragment_program);
        glLinkProgram(program);

        int  success;
        char infoLog[512];
        glGetShaderiv(program, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        glDeleteShader(vertex_program);
        glDeleteShader(fragment_program);
    }
};
#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Camera.h"
#include "Shader.h"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

Camera cam;
Shader shader;

GLuint vao = 0;
GLuint vertex_buffer = 0;
int vertex_count = 0;


float vertices[] = {
    -0.5, -0.5, -2,
     0.5, -0.5, -2,
     -0.5,  0.5, -2,
     0.5,  0.5, -2,
      0.5, -0.5, -2,
     -0.5,  0.5, -2
};



void init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glViewport(0, 0, WIDTH, HEIGHT);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
   
    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    vertex_count = 6;

    shader.compileShader("vertex_shader.glsl", "fragment_shader.glsl");
}

void release()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vertex_buffer);

    glDeleteShader(shader.program);
}

void draw()
{
    glClearColor(0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(vao);
    glUseProgram(shader.program);

    glm::mat4 view = cam.getViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glm::mat4 vp_matrix = projection * view;

    glUniformMatrix4fv(glGetUniformLocation(shader.program, "vp"), 1, GL_FALSE, &vp_matrix[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, vertex_count);
}

// resize window when resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}





int main()
{    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    // need to be called after the window creation
    init();


    while (!glfwWindowShouldClose(window))
    {
        cam.processInput(window);
        draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
   
    release();
    glfwTerminate();
    return 0;
}


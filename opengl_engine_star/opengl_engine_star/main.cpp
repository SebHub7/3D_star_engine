#define GLFW_DLL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"

const unsigned int WINDOW_WIDTH = 800;
const unsigned int WINDOW_HEIGHT = 600;

Camera cam;
Mesh m;
Shader shader;


void init()
{
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    m = read_obj("cone.obj");
    m.initBuffers();

    //cam.lookAt(m.getObjectCenter());

    shader.compileShader("vertex_shader.glsl", "fragment_shader.glsl");
}


void draw()
{
    glClearColor(0.2, 0.2, 0.2, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(m.vao);
    glUseProgram(shader.program);

    glm::mat4 view = cam.getViewMatrix();
    glm::mat4 projection = cam.getPerspectiveProjectionMatrix(WINDOW_WIDTH, WINDOW_HEIGHT);
    glm::mat4 vp_matrix = projection * view;

    glUniformMatrix4fv(glGetUniformLocation(shader.program, "vp"), 1, GL_FALSE, &vp_matrix[0][0]);

    glDrawArrays(GL_TRIANGLES, 0, m.vertices.size());
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
   
    glfwTerminate();
    return 0;
}


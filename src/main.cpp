#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <vector>

#include "Engine/Engine.h"

using namespace Engine;

int main()
{
    std::cout << "We meet again." << std::endl;

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    uint32_t gameWidth = 1280, gameHeight = 720;

    GLFWwindow* window = glfwCreateWindow(gameWidth, gameHeight, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetWindowAttrib(window, GLFW_RESIZABLE, GLFW_FALSE);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {        
        std::cout << "Failed to initialize GLAD!" << std::endl;
        exit(EXIT_FAILURE);
    }
    
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    // Set the function that will be triggered by the callback, the second parameter
    // is the data parameter of the callback, it can be useful for different
    // contexts but isn't necessary for our simple use case.
    glDebugMessageCallback(GLUtils::GLDebugMessageCallback, 0);
    
    // ok, let's see how much I can do from memory

    std::vector<VertexPositionColor> vertexDataTriangle =
    {
        VertexPositionColor{glm::vec3( 0.0f, 40.0f, 0.0f), glm::vec3(0.906f,0.235f, 0.0f)},
        VertexPositionColor{glm::vec3( 20.0f, 0.0f, 0.0f), glm::vec3(0.906f,0.235f, 0.0f)},
        VertexPositionColor{glm::vec3(-20.0f, 0.0f, 0.0f), glm::vec3(0.906f,0.235f, 0.0f)}
    };

    std::vector<VertexPositionColor> vertexDataSquare =
    {
        VertexPositionColor{glm::vec3(-25,   25, 0), glm::vec3(0.906f,0.235f, 0.0f)},
        VertexPositionColor{glm::vec3( 25,   25, 0), glm::vec3(0.906f,0.235f, 0.0f)},
        VertexPositionColor{glm::vec3( 25,  -25, 0), glm::vec3(0.906f,0.235f, 0.0f)},
        VertexPositionColor{glm::vec3(-25,  -25, 0), glm::vec3(0.906f,0.235f, 0.0f)}
    };

    std::vector<uint16_t> triangleIndices = 
    {
        0, 1, 2
    };

    std::vector<uint16_t> squareIndices = 
    {
        0, 1, 2,
        0, 2, 3
    };

    Shader shader("Shaders/vertex.vert", "Shaders/fragment.frag");
    
    VertexBuffer vb = VertexBuffer(&(vertexDataSquare[0]), vertexDataSquare.size() * sizeof(VertexPositionColor));
    VertexArray va(&VertexPositionColor::Attributes);
    IndexBuffer ib = IndexBuffer(&squareIndices[0], squareIndices.size());

    Viewport viewport(gameWidth, gameHeight);
    viewport.Set();

    Camera2D camera(viewport);
    
    glm::mat4 squareTransform(1.0f);
    glm::vec3 squarePosition(viewport.Width() / 2.0f, viewport.Height() / 2.0f, 0.0f);

    float time;
    float angle = 0;
    glm::vec3 color = glm::vec3(0, 1, 0);

    glClearColor(0.392, 0.584, 0.929, 1);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        camera.Update(0.0f);

        // update square transform
        time = glfwGetTime();
        angle += 3.14 / 360;

        squareTransform = glm::translate(squarePosition);
        squareTransform = glm::scale(squareTransform, glm::vec3(sin(time) * 1.5 + 2));
        squareTransform = glm::rotate(squareTransform, angle, glm::vec3(0, 0, 1));

        shader.use();
        shader.setVec3("uColor", color);
        shader.setFloat("uTime", time);
        shader.setMat4("uModel", squareTransform);
        shader.setMat4("uView", camera.GetViewTransform());
        shader.setMat4("uProjection", camera.GetViewProjectionTransform());

        va.Bind();
        glDrawElements(GL_TRIANGLES, ib.GetDataCount(), GL_UNSIGNED_SHORT, 0);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    vb.Delete();

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);

}
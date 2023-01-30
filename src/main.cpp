#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

int windowSize_X = 640;
int windowSize_Y = 480;

void glWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    windowSize_X = width;
    windowSize_Y = height;
    glViewport(0, 0, windowSize_X, windowSize_Y);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scanCode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}

int main( void )
{
    /* Initialize the library */
    if (!glfwInit())
    {
        std::cout << "glfwInit failed!" << std::endl;
        return -1;
    }
        
    // showing a version of glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(windowSize_X, windowSize_Y, "BattleCity", nullptr, nullptr);
    if ( !pWindow )
    {
        std::cout << "glfwCreateWindow failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    /* Make the window's context current */
    glfwMakeContextCurrent( pWindow );

    if ( !gladLoadGL() )
    {
        std::cout << "Can't load Glad!" << std::endl;
        return -1;
    }

    std::cout << "Rendered: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    // std::cout << "OpenGL: " << GLVersion.major << "." << GLVersion.minor << std::endl;

    glClearColor( 0, 1, 0, 1 );

    /* Loop until the user closes the window */
    while ( !glfwWindowShouldClose( pWindow ) )
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers( pWindow );

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
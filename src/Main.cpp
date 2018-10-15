////////////////////////////////////////////////////////////////
/// Main.cpp
////////////////////////////////////////////////////////////////

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other includes
#include "Shader.h"

// Window Dimensions
const GLint WIDTH = 800, HEIGHT = 600;

int main( )
{
    glfwInit( );

    // set all the required options for GLFW
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint ( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

    glfwWindowHint ( GLFW_RESIZABLE, GL_FALSE );

    // create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow ( WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr );

    int screenWidth, screenHeight;
    glfwGetFramebufferSize ( window, &screenWidth, &screenHeight );

    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent ( window );

    // Set this to true so FLEW knows to use a modern approach to retrieving function points and extensions
    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport ( 0, 0, screenWidth, screenHeight );

    // Build and compile our shader program
    Shader ourShader( "resources/shaders/core.vert", "resources/shaders/core.frag" );

    GLfloat vertices[] = {
        // Positions            // Colors
        0.5f, -0.5f, 0.0f,      0.39f, 0.11f, 0.70f,  // Bottom Right
        -0.5f, -0.5f, 0.0f,     0.31f, 0.7f, 0.07f,   // Bottom Left
        0.0f,  0.5f, 0.0f,      1.0f, 0.46f, 0.26f    // Top
    };

    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s)
    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    // Position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );

    // Color attribute
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 1 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    // Note that this is allowed, the call to glVertexAttribPointer
    // registered VBO as the currently bound vertex buffer object so
    // afterwards we can safely unbind

    glBindVertexArray( 0 );
    // Unbind VAO (it's always a good ting to unbind any buffer/array to prevent strange bugs)

    // Game loop
    while ( !glfwWindowShouldClose( window ) )
    {
        // check if any events have been activated (key press, mouse, etc)
        glfwPollEvents( );

        // Render
        // Clear the colorbuffer
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT );

        // Draw our first triangle
        ourShader.Use( );
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 3 );
        glBindVertexArray( 0 );

        // swap the screen buffers
        glfwSwapBuffers( window );
    }

    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );

    return EXIT_SUCCESS;
}

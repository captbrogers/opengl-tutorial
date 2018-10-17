////////////////////////////////////////////////////////////////
/// Main.cpp
////////////////////////////////////////////////////////////////

#include <iostream>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other libraries
#include "SOIL2/SOIL2.h"

// Other includes
#include "Shader.h"

// Window Dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

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

    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

    // Build and compile our shader program
    Shader ourShader( "resources/shaders/core.vert", "resources/shaders/core.frag" );

    GLfloat vertices[] = {
        // Positions         // Colors           // Texture Coords
         0.5f,  0.5, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
         0.5f, -0.5, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
        -0.5f,  0.5, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
    };

    GLuint indices[] = {
        0, 1, 3,  // First Triangle
        1, 2, 3   // Second Triangle
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    glGenBuffers( 1, &EBO );

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s)
    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

    // Position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );

    // Color attribute
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 1 );

    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof( GLfloat ), ( GLvoid * )( 6 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 2 );

    // Note that this is allowed, the call to glVertexAttribPointer
    // registered VBO as the currently bound vertex buffer object so
    // afterwards we can safely unbind
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    // Unbind VAO (it's always a good ting to unbind any buffer/array to prevent strange bugs)
    glBindVertexArray( 0 );

    // Load and create a texture
    GLuint texture;
    int width, height;
    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );

    // Set texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    
    // Set texture filtering
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    // Load the image, create a texture from it
    unsigned char *image = SOIL_load_image( "resources/images/image1.jpg", &width, &height, 0, SOIL_LOAD_RGBA );
    std::cout << "SOIL_load_image *image = " << SOIL_last_result() << std::endl;
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );

    // Generate mipmaps
    glGenerateMipmap( GL_TEXTURE_2D );

    // free the resources for the image
    SOIL_free_image_data( image );
    glBindTexture( GL_TEXTURE_2D, 0 );

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
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, texture );
        glUniform1i( glGetUniformLocation( ourShader.Program, "ourTexture" ), 0 );

        // Draw container
        glBindVertexArray( VAO );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        glBindVertexArray( 0 );

        // swap the screen buffers
        glfwSwapBuffers( window );
    }

    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    glDeleteBuffers( 1, &EBO );

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate( );

    return EXIT_SUCCESS;
}

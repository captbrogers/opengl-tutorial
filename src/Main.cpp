////////////////////////////////////////////////////////////////
/// Main.cpp
////////////////////////////////////////////////////////////////

#include <iostream>
#include <ctime>

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// OpenGL Math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other libraries
#include "SOIL2/SOIL2.h"

// Other includes
#include "Shader.h"

// Window Dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

int main( )
{
    // seed the RNG
    srand( time(NULL) );

    glfwInit( );

    // set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );

    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

    // create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr );

    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );

    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent( window );

    // Set this to true so FLEW knows to use a modern approach to retrieving function points and extensions
    glewExperimental = GL_TRUE;

    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport( 0, 0, screenWidth, screenHeight );
    glEnable( GL_DEPTH_TEST );

    // Build and compile our shader program
    Shader ourShader( "resources/shaders/core.vert", "resources/shaders/core.frag" );

    GLfloat vertices[] = {
        // Positions            // Texture Coords
       -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,     0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,

       -0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,     1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,     1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,     1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,     0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,     0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,     0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,     1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,     1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,     0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,     0.0f, 1.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s)
    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    // Position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );

    // Texture attribute
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), ( GLvoid * )( 3 * sizeof( GLfloat ) ) );
    glEnableVertexAttribArray( 2 );

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
    unsigned char *image = SOIL_load_image( "resources/images/unsplash_image1.jpg", &width, &height, 0, SOIL_LOAD_RGBA );
    std::cout << "SOIL_load_image *image = " << SOIL_last_result() << std::endl;
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image );

    // Generate mipmaps
    glGenerateMipmap( GL_TEXTURE_2D );

    // free the resources for the image
    SOIL_free_image_data( image );
    glBindTexture( GL_TEXTURE_2D, 0 );

    glm::mat4 projection;
    projection = glm::perspective( 45.0f, ( GLfloat )screenWidth / ( GLfloat )screenHeight, 0.1f, 100.0f);

    // Game loop
    while ( !glfwWindowShouldClose( window ) )
    {
        // check if any events have been activated (key press, mouse, etc)
        glfwPollEvents( );

        // Render
        // Clear the colorbuffer
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Activate and bind texture
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, texture );
        glUniform1i( glGetUniformLocation( ourShader.Program, "ourTexture" ), 0 );

        // Draw our first triangle
        ourShader.Use( );

        // Create transformations
        glm::mat4 model;
        glm::mat4 view;
        model = glm::rotate( model, ( GLfloat )glfwGetTime( ) * 1.0f, glm::vec3( 0.5f, 1.0f, 0.0f ) );
        view = glm::translate( view, glm::vec3( 0.0f, 0.0f, -3.0f ) );

        GLint modelLoc = glGetUniformLocation( ourShader.Program, "model" );
        GLint viewLoc = glGetUniformLocation( ourShader.Program, "view" );
        GLint projLoc = glGetUniformLocation( ourShader.Program, "projection" );

        glUniformMatrix4fv( modelLoc, 1, GL_FALSE, glm::value_ptr( model ) );
        glUniformMatrix4fv( viewLoc, 1, GL_FALSE, glm::value_ptr( view ) );
        glUniformMatrix4fv( projLoc, 1, GL_FALSE, glm::value_ptr( projection ) );

        // Draw container
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 36 );
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

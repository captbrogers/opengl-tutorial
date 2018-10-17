#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(position, 1.0);
    ourColor = color;

    // Swapping y-axis by subtracting our coords form 1.
    // This is because most images have top y-axis
    // inversed with OpenGL's top y-axis.
    // TexCoord = texCoord;
    TexCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}
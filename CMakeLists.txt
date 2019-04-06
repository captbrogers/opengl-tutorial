cmake_minimum_required(VERSION 3.10)

project(opengl-tutorial VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(${PROJECT_NAME}
    src/Main.cpp
    src/Camera.h
    src/Shader.h
)

add_library(MY_SOIL STATIC
    src/SOIL2/etc1_utils.c
    src/SOIL2/etc1_utils.h
    src/SOIL2/image_DXT.c
    src/SOIL2/image_DXT.h
    src/SOIL2/image_helper.c
    src/SOIL2/image_helper.h
    src/SOIL2/jo_jpeg.h
    src/SOIL2/pkm_helper.h
    src/SOIL2/pvr_helper.h
    src/SOIL2/SOIL2.c
    src/SOIL2/SOIL2.h
    src/SOIL2/stbi_DDS_c.h
    src/SOIL2/stbi_DDS.h
    src/SOIL2/stbi_ext_c.h
    src/SOIL2/stbi_ext.h
    src/SOIL2/stb_image.h
    src/SOIL2/stb_image_write.h
    src/SOIL2/stbi_pkm_c.h
    src/SOIL2/stbi_pkm.h
    src/SOIL2/stbi_pvr_c.h
    src/SOIL2/stbi_pvr.h
)

target_link_libraries(${PROJECT_NAME}
    GL
    glfw
    GLEW
    SOIL
)

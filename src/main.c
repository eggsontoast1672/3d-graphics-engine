#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/image.h"
#include "engine/mesh.h"
#include "engine/shader.h"
#include "engine/texture.h"
#include "engine/window.h"

const char *const vertex_source =
    "#version 330 core\n"
    "layout (location = 0) in vec2 position;\n"
    "layout (location = 1) in vec2 tex_coord;\n"
    "out vec2 v_tex_coord;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(position, 0.0f, 1.0f);\n"
    "   v_tex_coord = tex_coord;\n"
    "}\n";

const char *const fragment_source =
    "#version 330 core\n"
    "in vec2 v_tex_coord;\n"
    "out vec4 f_color;\n"
    "uniform sampler2D u_texture;\n"
    "void main()\n"
    "{\n"
    "   f_color = texture(u_texture, v_tex_coord);\n"
    "}\n";

static void image_palette_test(const Image *image)
{
    for (size_t y = 0; y < image->height; y++)
    {
        for (size_t x = 0; x < image->width; x++)
        {
            uint8_t r = (uint8_t)((float)x / image->height * 255.0f);
            uint8_t g = (uint8_t)((float)y / image->height * 255.0f);
            uint8_t b = 0.0f;

            image_set_pixel(image, x, y, r, g, b);
        }
    }
}

int main()
{
    GLFWwindow *window = init_and_create_window(800, 600, "3D Graphics Engine");

    mesh_quad_init();

    GLuint program = shader_create(vertex_source, fragment_source);
    GLuint texture = texture_create();

    Image image;
    image_create(256, 256, &image);
    image_palette_test(&image);
    glBindTexture(GL_TEXTURE_2D, texture);
    texture_set_data(&image);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    image_delete(&image);
    glDeleteTextures(1, &texture);
    glDeleteProgram(program);
    mesh_quad_deinit();
    glfwTerminate();
}

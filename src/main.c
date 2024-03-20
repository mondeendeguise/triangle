#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include "filesystem.h"
#include "algebra.h"

const char *vertex_shader_path = "shaders/basic.vert";
const char *fragment_shader_path = "shaders/basic.frag";

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    (void) window;
    glViewport(0, 0, width, height);
}

typedef struct {
    V3f pos;
    V4f color;
} Vertex;

typedef enum {
    VA_POS = 0,
    VA_COLOR,
    VA_COUNT,
} Vertex_Attrib;

bool compile_shader_source(const GLchar *source, GLenum shader_type, GLuint *shader)
{
    *shader = glCreateShader(shader_type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);

    int compiled;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &compiled);

    if(!compiled) {
        GLsizei message_size;
        glGetShaderiv(*shader, GL_INFO_LOG_LENGTH, &message_size);
        GLchar message[message_size];

        glGetShaderInfoLog(*shader, message_size, &message_size, message);

        fprintf(stderr, "ERROR: failed to compile shader: %.*s\n", message_size, message);
        return false;
    }

    return true;
}

bool compile_shader_file(const char *file_path, GLenum shader_type, GLuint *shader)
{
    char *source = slurp_file(file_path);
    bool ok = compile_shader_source(source, shader_type, shader);
    free(source);
    return ok;
}

bool load_shader_program(const char *vertex_shader_path,
                         const char *fragment_shader_path,
                         GLuint *program)
{
    bool ok = true;
    GLuint vertex_shader, fragment_shader;
    ok = ok && compile_shader_file(vertex_shader_path, GL_VERTEX_SHADER, &vertex_shader);
    ok = ok && compile_shader_file(fragment_shader_path, GL_FRAGMENT_SHADER, &fragment_shader);

    *program = glCreateProgram();
    glAttachShader(*program, vertex_shader);
    glAttachShader(*program, fragment_shader);
    glLinkProgram(*program);

    int linked;
    glGetProgramiv(*program, GL_LINK_STATUS, &linked);
    if(!linked) {
        GLsizei message_size;
        glGetProgramiv(*program, GL_INFO_LOG_LENGTH, &message_size);
        GLchar message[message_size];

        glGetProgramInfoLog(*program, message_size, &message_size, message);

        fprintf(stderr, "ERROR: failed to load shader program: %.*s\n", message_size, message);
    }
    ok = ok && linked;

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return ok;
}

typedef enum {
    PROGRAM_BASIC = 0,
    PROGRAM_COUNT,
} Shader_Program;

typedef struct {
    GLuint vao;
    GLuint vbo;
    GLuint programs[PROGRAM_COUNT];
    Vertex *vertices;
    size_t vertex_count;
} Renderer;

static Renderer global_renderer = {0};

void r_init(Renderer *r)
{
    r->vertices = malloc(r->vertex_count * sizeof(Vertex));

    glGenBuffers(1, &r->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
    glBufferData(GL_ARRAY_BUFFER, r->vertex_count * sizeof(Vertex), r->vertices, GL_DYNAMIC_DRAW);

    glGenVertexArrays(1, &r->vao);
    glBindVertexArray(r->vao);

    glVertexAttribPointer(VA_POS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, pos));
    glEnableVertexAttribArray(VA_POS);

    glVertexAttribPointer(VA_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, color));
    glEnableVertexAttribArray(VA_COLOR);
}

void r_reload_shaders(Renderer *r)
{
    load_shader_program(vertex_shader_path, fragment_shader_path, &r->programs[0]);
    glUseProgram(r->programs[0]);
}

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
    if(!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glewInit();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Renderer *r = &global_renderer;
    r_init(r);
    r_reload_shaders(r);

    size_t vertex_count = 3;
    Vertex *vertices = malloc(vertex_count * sizeof(Vertex));
    
    vertices[0] = (Vertex) { v3f( 0.5f,  0.5f,  0.0f), v4f(1.0, 0.0, 0.0, 1.0) };
    vertices[1] = (Vertex) { v3f( 0.5f, -0.5f,  0.0f), v4f(0.0, 1.0, 0.0, 1.0) };
    vertices[2] = (Vertex) { v3f(-0.5f,  0.5f,  0.0f), v4f(0.0, 0.0, 1.0, 1.0) };

    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW);

    vertex_count = 6;
    vertices = realloc(vertices, vertex_count * sizeof(Vertex));

    vertices[3] = (Vertex) { v3f( 0.5f, -0.5f,  0.0f), v4f(1.0f, 0.0f, 0.0f, 1.0f) };
    vertices[4] = (Vertex) { v3f(-0.5f, -0.5f,  0.0f), v4f(0.0f, 1.0f, 0.0f, 1.0f) };
    vertices[5] = (Vertex) { v3f(-0.5f,  0.5f,  0.0f), v4f(0.0f, 0.0f, 1.0f, 1.0f) };

    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertices, GL_DYNAMIC_DRAW);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, vertex_count);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    if(vertices) free(vertices);
    return 0;
}

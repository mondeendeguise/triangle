#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

#include "filesystem.h"
#include "algebra.h"

const char *screen_shader_path = "shaders/screen.vert";
const char *basic_fragment_shader_path = "shaders/basic.frag";
const char *wireframe_shader_path = "shaders/wireframe.frag";

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    (void) window;
    glViewport(0, 0, width, height);
}

typedef struct {
    V2f pos;
    V2f uv;
    V4f color;
} Vertex;

typedef enum {
    VA_POS = 0,
    VA_UV,
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
    GLuint vertex_shader = 0;
    GLuint fragment_shader = 0;

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
    PROGRAM_WIREFRAME,
    PROGRAM_COUNT,
} Shader_Program;

#define VERTEX_CAP (8 * 1024)
#define INDEX_CAP (16 * 1024)
typedef struct {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;

    GLuint programs[PROGRAM_COUNT];

    Vertex vertices[VERTEX_CAP];
    size_t vertex_count;

    GLuint indices[INDEX_CAP];
    size_t index_count;

} Renderer;

static Renderer global_renderer = {0};

void r_init(Renderer *r)
{
    glGenVertexArrays(1, &r->vao);
    glBindVertexArray(r->vao);

    glGenBuffers(1, &r->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, r->vbo);
    glBufferData(GL_ARRAY_BUFFER, r->vertex_count * sizeof(Vertex), r->vertices, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &r->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, r->index_count * sizeof(GLuint), r->indices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(VA_POS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, pos));
    glEnableVertexAttribArray(VA_POS);

    glVertexAttribPointer(VA_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, uv));
    glEnableVertexAttribArray(VA_UV);

    glVertexAttribPointer(VA_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, color));
    glEnableVertexAttribArray(VA_COLOR);
}

void r_deallocate(Renderer *r)
{
    glDeleteVertexArrays(1, &r->vao);
    glDeleteBuffers(1, &r->vbo);
    glDeleteBuffers(1, &r->ebo);

    for(size_t i = 0; i < PROGRAM_COUNT; ++i) {
        glDeleteProgram(r->programs[i]);
    }
}

void r_reload_shaders(Renderer *r)
{
    load_shader_program(screen_shader_path, basic_fragment_shader_path, &r->programs[PROGRAM_BASIC]);
    load_shader_program(screen_shader_path, wireframe_shader_path, &r->programs[PROGRAM_WIREFRAME]);
    glUseProgram(r->programs[PROGRAM_BASIC]);
}

void toggle_wireframe(Renderer *r)
{
    GLint *polygon_mode = malloc(sizeof(GLint));  // avoid stack smashing error
    glGetIntegerv(GL_POLYGON_MODE, polygon_mode);
    switch(*polygon_mode) {
        case GL_FILL: {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glUseProgram(r->programs[PROGRAM_WIREFRAME]);
        } break;

        case GL_LINE:
        default: {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glUseProgram(r->programs[PROGRAM_BASIC]);
        } break;

    }
    free(polygon_mode);
}

void r_vertex(Renderer *r, Vertex v)
{
    assert(r->vertex_count < VERTEX_CAP);
    r->vertices[r->vertex_count++] = v;
}

void r_quad_pp(Renderer *r, V2f p1, V2f p2, V4f color)
{
    V2f a = p1;
    V2f b = v2f(p2.x, p1.y);
    V2f c = v2f(p1.x, p2.y);
    V2f d = p2;

    GLuint index_start = (GLuint) r->vertex_count;

    r_vertex(r, (Vertex){a, v2f(0.0f, 0.0f), color});
    r_vertex(r, (Vertex){b, v2f(1.0f, 0.0f), color});
    r_vertex(r, (Vertex){c, v2f(0.0f, 1.0f), color});
    r_vertex(r, (Vertex){d, v2f(1.0f, 1.0f), color});

    r->indices[r->index_count++] = index_start + 0;
    r->indices[r->index_count++] = index_start + 1;
    r->indices[r->index_count++] = index_start + 2;

    r->indices[r->index_count++] = index_start + 1;
    r->indices[r->index_count++] = index_start + 2;
    r->indices[r->index_count++] = index_start + 3;

    glBufferData(GL_ARRAY_BUFFER, r->vertex_count * sizeof(Vertex), r->vertices, GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, r->index_count * sizeof(GLuint), r->indices, GL_DYNAMIC_DRAW);
}

void r_quad_cr(Renderer *r, V2f center, V2f radius, V4f color)
{
    V2f p1 = v2f_sub(center, radius);
    V2f p2 = v2f_sum(center, radius);
    r_quad_pp(r, p1, p2, color);
}

int main(void)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "TRIANGLE", NULL, NULL);
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

    r_quad_pp(r, v2f(-0.5f, -0.5f), v2f(0.5f, 0.5f), v4f(1.0f, 0.0f, 1.0f, 1.0f));
    r_quad_cr(r, v2f(0.0f, 0.0f), v2ff(0.1f), v4f(1.0f, 0.0f, 0.0f, 1.0f));
    /* r_quad_pp(r, v2f( 0.0f, -0.5f), v2f( 0.5f,  0.5f), v4f(0.0f, 1.0f, 0.0f, 1.0f)); */
    /* r_quad_pp(r, v2f( 0.0f,  0.5f), v2f(-0.5f, -0.5f), v4f(0.0f, 1.0f, 0.0f, 1.0f)); */
    
    /* r_vertex(r, (Vertex) { v2f( 0.5f,  0.5f), v2f( 1.0,  1.0), v4f(1.0, 0.0, 0.0, 1.0) }); */
    /* r_vertex(r, (Vertex) { v2f( 0.5f, -0.5f), v2f( 1.0, -1.0), v4f(0.0, 1.0, 0.0, 1.0) }); */
    /* r_vertex(r, (Vertex) { v2f(-0.5f,  0.5f), v2f(-1.0,  1.0), v4f(0.0, 0.0, 1.0, 1.0) }); */

    /* glBufferData(GL_ARRAY_BUFFER, r->vertex_count * sizeof(Vertex), NULL, GL_DYNAMIC_DRAW); */

    /* r_vertex(r, (Vertex) { v2f(-0.5f, -0.5f), v2f(-1.0, -1.0), v4f(1.0f, 0.0f, 0.0f, 1.0f) }); */
    /* r_vertex(r, (Vertex) { v2f( 0.5f, -0.5f), v2f( 1.0, -1.0), v4f(0.0f, 1.0f, 0.0f, 1.0f) }); */
    /* r_vertex(r, (Vertex) { v2f(-0.5f,  0.5f), v2f(-1.0,  1.0), v4f(0.0f, 0.0f, 1.0f, 1.0f) }); */

    /* glBufferData(GL_ARRAY_BUFFER, r->vertex_count * sizeof(Vertex), r->vertices, GL_DYNAMIC_DRAW); */

    toggle_wireframe(r);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* glDrawArrays(GL_TRIANGLES, 0, r->vertex_count); */
        glDrawElements(GL_TRIANGLES, r->index_count, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    r_deallocate(r);
    glfwTerminate();
    return 0;
}

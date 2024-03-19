#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

char *slurp_file(const char *file_path)
{
    char *buf = NULL;
    FILE *f = NULL;

    f = fopen(file_path, "r");
    if(f == NULL) goto defer;
    if(fseek(f, 0, SEEK_END) < 0) goto defer;

    long size = ftell(f);
    if(size < 0) goto defer;

    // size should be equal to the files length
    buf = malloc(size + 1);
    if(buf == NULL) goto defer;

    if(fseek(f, 0, SEEK_SET) < 0) goto defer;

    fread(buf, 1, size, f);
    if(ferror(f)) goto defer;

    buf[size] = '\0';

    if(f) {
        fclose(f);
        errno = 0;
    }
    return buf;

defer:
    if(f) {
        int serr = errno;
        fclose(f);
        errno = serr;
    }
    if(buf) {
        free(buf);
    }

    return NULL;
}

const char *vertex_shader_path = "shaders/basic.vert";
const char *fragment_shader_path = "shaders/basic.frag";

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    (void) window;
    glViewport(0, 0, width, height);
}

typedef struct { float x, y, z; } V3f;
typedef struct { float x, y, z, w; } V4f;

V3f v3f(float x, float y, float z)
{
    return (V3f){x, y, z};
}

V4f v4f(float x, float y, float z, float w)
{
    return (V4f){x, y, z, w};
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

    char *vertex_shader_source = slurp_file(vertex_shader_path);
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, (const char * const *) &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);
    free(vertex_shader_source);

    char *fragment_shader_source = slurp_file(fragment_shader_path);
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, (const char * const *) &fragment_shader_source, NULL);
    glCompileShader(fragment_shader);
    free(fragment_shader_source);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    size_t vertex_count = 3;
    Vertex *vertices = malloc(vertex_count * sizeof(Vertex));
    
    vertices[0] = (Vertex) { v3f(-0.5f, -0.5f,  0.0f), v4f(1.0, 0.0, 0.0, 1.0) };
    vertices[1] = (Vertex) { v3f( 0.5f, -0.5f,  0.0f), v4f(0.0, 1.0, 0.0, 1.0) };
    vertices[2] = (Vertex) { v3f( 0.0f,  0.5f,  0.0f), v4f(0.0, 0.0, 1.0, 1.0) };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * sizeof(Vertex), vertices, GL_DYNAMIC_DRAW);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glVertexAttribPointer(VA_POS, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, pos));
    glEnableVertexAttribArray(VA_POS);

    glVertexAttribPointer(VA_COLOR, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, color));
    glEnableVertexAttribArray(VA_COLOR);

    glUseProgram(shader_program);

    while(!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    if(vertices) free(vertices);
    return 0;
}

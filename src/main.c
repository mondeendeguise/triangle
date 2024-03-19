#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

bool compile_shader_source(const GLchar *source, GLenum shader_type, GLuint *shader)
{
    *shader = glCreateShader(shader_type);
    glShaderSource(*shader, 1, &source, NULL);

    int compiled;
    glCompileShader(*shader);
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

    GLuint vertex_shader, fragment_shader;
    compile_shader_file(vertex_shader_path, GL_VERTEX_SHADER, &vertex_shader);
    compile_shader_file(fragment_shader_path, GL_FRAGMENT_SHADER, &fragment_shader);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    size_t vertex_count = 3;
    Vertex *vertices = malloc(vertex_count * sizeof(Vertex));
    
    vertices[0] = (Vertex) { v3f( 0.5f,  0.5f,  0.0f), v4f(1.0, 0.0, 0.0, 1.0) };
    vertices[1] = (Vertex) { v3f( 0.5f, -0.5f,  0.0f), v4f(0.0, 1.0, 0.0, 1.0) };
    vertices[2] = (Vertex) { v3f(-0.5f,  0.5f,  0.0f), v4f(0.0, 0.0, 1.0, 1.0) };

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

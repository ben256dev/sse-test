#include <openssl/rand.h>
#include <butil/butil.h>
#include <time.h>
#include <stdio.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef float v3[3];

int run_vector_stuff(GLuint program)
{
#define VECTOR_COUNT 8388608
#define VECTORS_BYTES VECTOR_COUNT * sizeof(v3)
    v3* vectors = xmalloc(VECTORS_BYTES);

    if (RAND_bytes((unsigned char*)vectors, VECTORS_BYTES) != 1)
        die("RAND_bytes()");

    GLuint query;
    glGenQueries(1, &query);
    glQueryCounter(query, GL_TIMESTAMP);

    GLuint ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferStorage(GL_SHADER_STORAGE_BUFFER, VECTORS_BYTES, vectors,
            GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

    v3* mapped_data = (v3*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, VECTORS_BYTES,
                                            GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
    if (!mapped_data)
        die("glMapBufferRange()");

    glUseProgram(program);
    glDispatchCompute(VECTOR_COUNT / 2 / 256, 1, 1);
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
    glDeleteBuffers(1, &ssbo);

    GLuint query_end;
    glGenQueries(1, &query_end);
    glQueryCounter(query_end, GL_TIMESTAMP);

    GLuint64 start_time;
    GLuint64 end_time;

    glGetQueryObjectui64v(query, GL_QUERY_RESULT, &start_time);
    glGetQueryObjectui64v(query_end, GL_QUERY_RESULT, &end_time);

    GLuint64 elapsed_time = (end_time - start_time) / 1000;
    
    printf("%llu\n", elapsed_time);
    glDeleteProgram(program);
    glfwTerminate();

    free(vectors);

    return 0;
}

GLuint run_opengl_stuff()
{
    if (!glfwInit())
        die("glfwInit()");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(1, 1, "empty", NULL, NULL);
    if (!window)
        die("glfwCreateWindow()");
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        die("gladLoadGLLoader()");

    char* shader_source = xmfopen("compute_shader.glsl");
    GLuint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute_shader, 1, (const char**)&shader_source, NULL);
    glCompileShader(compute_shader);
    free(shader_source);
    
    GLint success;
    glGetShaderiv(compute_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(compute_shader, 512, NULL, info_log);
        die("glCompileShader: %s\n", info_log);
    }

    GLuint program = glCreateProgram();
    glAttachShader(program, compute_shader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetProgramInfoLog(program, 512, NULL, info_log);
        die("glLinkProgram: %s\n", info_log);
    }

    glDeleteShader(compute_shader);

    return program;
}

int main(void)
{
    GLuint program = run_opengl_stuff();
    run_vector_stuff(program);
    return 0;
}

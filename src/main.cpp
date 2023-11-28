#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
 
#include "linmath.h"
 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#define DllExport __declspec(dllexport)
#include <limits>

using namespace std;

static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};

/* static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { 0.f, 0.f, 0.f, 0.f, 0.f },
    {  0.f, 0.f, 0.f, 0.f, 0.f },
    {   0.f,  0.f, 0.f, 0.f, 1.f }
}; */
 
static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";

float ratio;
int width, height;
mat4x4 m, p, mvp;
GLuint program;
GLint mvp_location, vpos_location, vcol_location;
float* added;
float* coord_x;
float* coord_y;
int *should_loop;

void rotate(GLFWwindow* window, GLuint *program, float added_new, bool loop = false, bool increase = false)
{
    
    *added = added_new;
    if(loop && *should_loop != 1 )
    {

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
   
        mat4x4_identity(m);
        mat4x4_translate(m, *coord_x, *coord_y, m[3][2]);
        mat4x4_rotate_Y(m, m, *added);
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        mat4x4 *amogus = &m;

        glUseProgram(*program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glUniformMatrix4fv(vcol_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, 4);
        glDrawArrays(GL_TRIANGLES, 0, 4);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void move_x(GLFWwindow* window, int key, float amount)
{
    if(glfwGetKey(window, key) == GLFW_PRESS){
        *should_loop = 1;
    } else {
        *should_loop = 0;
    }
    cout << "should_loop: " << *should_loop << endl;
    while(glfwGetKey(window, key) == GLFW_PRESS){
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        *coord_x = *coord_x + amount;
        mat4x4_identity(m);
        m[3][0] = *coord_x;
        m[3][1] = *coord_y;
        float angle = *added;
        cout << "Angle: " << *added << endl;
        mat4x4_rotate_Y(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glUniformMatrix4fv(vcol_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, 4);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    if(glfwGetKey(window, key) == GLFW_PRESS){
        *should_loop = 1;
    } else {
        *should_loop = 0;
    }
    cout << "should_loop: " << *should_loop << endl;
    
}

void move_y(GLFWwindow* window, int key, float amount)
{
    if(glfwGetKey(window, key) == GLFW_PRESS){
        *should_loop = 1;
    } else {
        *should_loop = 0;
    }
    cout << "should_loop: " << *should_loop << endl;
    while(glfwGetKey(window, key) == GLFW_PRESS){
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        *coord_y = *coord_y + amount;
        float angle = *added;
        mat4x4_identity(m);
        mat4x4_translate(m, *coord_x, *coord_y, m[3][2]);
        mat4x4_rotate_Y(m, m, (float) glfwGetTime());
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        mat4x4_mul(mvp, p, m);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glUniformMatrix4fv(vcol_location, 1, GL_FALSE, (const GLfloat*) mvp);
        glDrawArrays(GL_TRIANGLES, 0, 4);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    if(glfwGetKey(window, key) == GLFW_PRESS){
        *should_loop = 1;
    } else {
        *should_loop = 0;
    }
    cout << "should_loop: " << *should_loop << endl;
    
}

void printInt(int *printable)
{
    cout << *printable << endl;
}
 
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_A && action == GLFW_PRESS)
    {
        //rotate(window, &program, (float) 2);
        printInt(&key);
        move_x(window,key, -0.05f);
    }
    if(key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        //rotate(window, &program, (float) 2, false, true);
        int* sixty_nine;
        *sixty_nine = 69;
        move_x(window, key, 0.05f);
       
        printInt(sixty_nine);
    }
    if(key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        //rotate(window, &program, (float) 2);
        printInt(&key);
        move_y(window,key, 0.05f);
    }
    if(key == GLFW_KEY_S && action == GLFW_PRESS)
    {
        //rotate(window, &program, (float) 2, false, true);
        move_y(window, key, -0.05f); 
        printInt(&key);
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main(void)
{
    added = (float* ) malloc(sizeof(float));
    coord_x = (float*) malloc(sizeof(float));
    coord_y = (float*) malloc(sizeof(float));
    should_loop = (int*) malloc(sizeof(int));
    *added = 0;
    *coord_x = 0;
    *coord_y = 0;
    *should_loop = 0;
    GLFWwindow* window;
    GLuint vertex_buffer, vertex_shader, fragment_shader;
 
    glfwSetErrorCallback(error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    int* count = (int*) malloc(sizeof(int));

    GLFWmonitor **monitors = (GLFWmonitor**) malloc(500000000000);
    
    monitors = glfwGetMonitors(count);

 
    cout << count << endl;

    window = glfwCreateWindow(640, 480, "Among Us 2 (VERY LEGIT)!!!!!", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
 
    glfwSetKeyCallback(window, key_callback);
 
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glfwSwapInterval(1);

    cout << "OpenGL loaded :) I like LEGOs" << endl;
 
    // NOTE: OpenGL error checks have been omitted for brevity
 
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
 
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
 
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
 
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
 
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) (sizeof(float) * 2));
 
    while (!glfwWindowShouldClose(window))
    {
        rotate(window, &program, (float) glfwGetTime(), true);
    }
 
    glfwDestroyWindow(window);
    free(count);
    free(monitors);
    glfwTerminate();
    cout << "Exit :) Good luck! Have Nice day!!" << endl;
    cout << ":) I like airplanes" << endl;
    exit(EXIT_SUCCESS);
}
 
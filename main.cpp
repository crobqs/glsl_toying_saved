#include "include/glad/glad.h"
#include "glfw-3.4/include/GLFW/glfw3.h"
#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <cxxabi.h>
#include <memory>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.hpp"


struct {
    GLFWwindow* window;
    float lastTime;
    float curTime;
    float deltaTime;
    Shader* shader;
    GLuint vao;
    GLuint vbo;
    float clickTime;
    glm::vec2 clickPos;
} g;

static void run();
static void init(int width, int height);
static void destroy();
static void gameLoop();
static void setup();
static void update(float dt);
static void render();
static void processInput(float dt);
static void clearBackground(float r, int g, float b);
static float getTime();
static float updateDelta();
static void framebufferSizeCallback(GLFWwindow* window, int width, int height);


int main() {
    run();
}


static void run() {
    init(800, 800);
    gameLoop();
    destroy();
}

static void init(int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    g.window = glfwCreateWindow(width, height, "", NULL, NULL);
    glfwMakeContextCurrent(g.window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSetFramebufferSizeCallback(g.window, framebufferSizeCallback);
    glViewport(0, 0, width, height);
}

static void destroy() {
    glDeleteVertexArrays(1, &g.vao);
    glDeleteBuffers(1, &g.vbo);
    delete g.shader;
    glfwDestroyWindow(g.window);
    glfwTerminate();
}

static void gameLoop() {
    setup();
    while (!glfwWindowShouldClose(g.window)) {
        float dt = updateDelta();
        update(dt);
        render();
    }
}

static void setup() {
    float vert[] = {
        -1.0f, -1.0f,
        3.0f, -1.0f,
        -1.0f, 3.0f
    };
    glGenVertexArrays(1, &g.vao);
    glGenBuffers(1, &g.vbo);
    glBindVertexArray(g.vao);
    glBindBuffer(GL_ARRAY_BUFFER, g.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof vert, vert, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    g.shader = new Shader("shaders/default.vert", "shaders/default.frag");
    g.lastTime = g.curTime = getTime();
    g.deltaTime = 0.0f;
}

static void update(float dt) {
    glfwPollEvents();
    processInput(dt);
}

static void render() {
    int widthi, heighti;
    double xposd, yposd;
    glfwGetFramebufferSize(g.window, &widthi, &heighti);
    glfwGetCursorPos(g.window, &xposd, &yposd);

    float width, height, xpos, ypos;
    width = widthi;
    height = heighti;
    xpos = xposd;
    ypos = yposd;

    g.shader->activate();
    glBindVertexArray(g.vao);
    
    g.shader->setUniform1f("time", getTime());
    g.shader->setUniform2f("resolution", width, height);
    g.shader->setUniform2f("mpos", xpos, ypos);
    g.shader->setUniform1f("clickTime", g.clickTime);
    g.shader->setUniform2fv("clickPos", glm::value_ptr(g.clickPos));
    
    clearBackground(0.0f, 0.0f, 0.0f);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glBindVertexArray(0);
    g.shader->deactivate();
    
    glfwSwapBuffers(g.window);
}

static void processInput(float dt) {
    if (glfwGetKey(g.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(g.window, 1);
    }
    if (glfwGetKey(g.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        g.clickTime = getTime();
        double x, y;
        glfwGetCursorPos(g.window, &x, &y);
        g.clickPos = glm::vec2((float)x, (float)y);
    }
}

static void clearBackground(float r, int g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static float getTime() {
    return (float)glfwGetTime();
}

static float updateDelta() {
    g.curTime = getTime();
    g.deltaTime = g.curTime - g.lastTime;
    g.lastTime = g.curTime;
    return g.deltaTime;
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

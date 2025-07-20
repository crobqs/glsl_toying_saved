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
} g;

static void run();
static void init(int width, int height);
static void destroy();
static void gameLoop();
static void gameLoopRun();
static void processInput();
static void clearBackground(float r, int g, float b);


int main() {
    // run();
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
}

static void destroy() {
    glfwDestroyWindow(g.window);
    glfwTerminate();
}

static void gameLoop() {
    while (!glfwWindowShouldClose(g.window)) {
        gameLoopRun();
    }
}

static void gameLoopRun() {
    glfwPollEvents();
    processInput();
    clearBackground(0.0f, 0.0f, 0.0f);
    glfwSwapBuffers(g.window);
}

static void processInput() {
    if (glfwGetKey(g.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(g.window, 1);
    }
}

static void clearBackground(float r, int g, float b) {
    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

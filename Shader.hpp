#ifndef SHADER_HPP
#define SHADER_HPP

#include <stdio.h>
#include <stdlib.h>
#include "include/glad/glad.h"
#include <vector>

class Shader {
public:
    GLuint id;
    Shader() = delete;
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(const Shader&&) = delete;
    Shader& operator=(const Shader&&) = delete;
    Shader(const char* vertexShaderFilename, const char* fragmentShaderFilename);
    ~Shader();
    void activate();
    void deactivate();
    void setUniform1i(const char* name, int v0);
    void setUniform1f(const char* name, float v0);
    void setUniform2f(const char* name, float v0, float v1);
    void setUniform2fv(const char* name, const float* value);
    void setUniform3fv(const char* name, const float* value);
    void setUniform4fv(const char* name, const float* value);
    void setUniformMatrix3fv(const char* name, const float* value);

private:
    char* getFileContent(const char* filename);
    GLuint createShader(const char* filename, GLenum type);
    GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
    int getLoc(const char* uniformName);
};

#endif

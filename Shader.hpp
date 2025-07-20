#ifndef SHADER_HPP
#define SHADER_HPP

#include <stdio.h>
#include <stdlib.h>
#include "include/glad/glad.h"

class Shader {
public:
    GLuint id;
    Shader(const char* vertexShader, const char* fragmentShader);

private:
    char* getFileContent(const char* filename);
};

#endif
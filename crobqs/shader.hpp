#include "include/glad/glad.h"
#include "glfw-3.4/include/GLFW/glfw3.h"
#include <iostream>
#include <vector>
#include <string>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>

class Shader {
public:
    unsigned int id;
    Shader(std::string vertexSrcFile, std::string fragmentSrcFile);
    ~Shader();
private:
    void checkCompileErrors(unsigned int id_, const char* type);
    unsigned int prepareShader(std::string vertexSrcFile, const char* type);
};
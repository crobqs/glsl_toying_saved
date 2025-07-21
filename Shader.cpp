#include "Shader.hpp"

Shader::Shader(const char* vertexShaderFilename, const char* fragmentShaderFilename) {
    GLuint vertexShader = createShader(vertexShaderFilename, GL_VERTEX_SHADER);
    GLuint fragmentShader = createShader(fragmentShaderFilename, GL_FRAGMENT_SHADER);
    id = createProgram(vertexShader, fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::activate() {
    glUseProgram(id);
}

void Shader::deactivate() {
    glUseProgram(0);
}

char* Shader::getFileContent(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        perror("fopen");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    rewind(f);

    char* fileContent = (char*)calloc(len + 1, 1);
    if (!fileContent) {
        perror("calloc");
        fclose(f);
        return NULL;
    }

    size_t freadLen = fread(fileContent, 1, len, f);
    if ((long)freadLen != len) {
        perror("fread");
    }

    fclose(f);
    return fileContent;
}

GLuint Shader::createShader(const char* filename, GLenum type) {
    GLuint shaderId = glCreateShader(type);
    char* shaderSrc = getFileContent(filename);
    glShaderSource(shaderId, 1, &shaderSrc, NULL);
    glCompileShader(shaderId);
    int isCompiled;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE) {
        const char* shaderType = type == GL_VERTEX_SHADER ? "GL_VERTEX_SHADER"
            : type == GL_FRAGMENT_SHADER ? "GL_FRAGMENT_SHADER"
            : "UNKNOWN";
        printf("%s compilation failed : '%s'\n", shaderType, filename);
        int infoLogLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> infoLog(infoLogLength);
        glGetShaderInfoLog(shaderId, infoLogLength, NULL, infoLog.data());
        puts(infoLog.data());
        glDeleteShader(shaderId);
    }
    free(shaderSrc);
    return shaderId;
}

GLuint Shader::createProgram(GLuint vertexShader, GLuint fragmentShader) {
    GLuint programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);
    int isLinked;
    glGetProgramiv(programId, GL_LINK_STATUS, &isLinked);
    if (isLinked == GL_FALSE) {
        printf("Program linking failed");
        int infoLogLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> infoLog(infoLogLength);
        glGetProgramInfoLog(programId, infoLogLength, NULL, infoLog.data());
        puts(infoLog.data());
        glDeleteProgram(programId);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return programId;
}

int Shader::getLoc(const char* uniformName) {
    return glGetUniformLocation(id, uniformName);
}

void Shader::setUniform1i(const char* name, int v0) {
    int loc = getLoc(name);
    glUniform1i(loc, v0);
}

void Shader::setUniform1f(const char* name, float v0) {
    int loc = getLoc(name);
    glUniform1f(loc, v0);
}

void Shader::setUniform2f(const char* name, float v0, float v1) {
    int loc = getLoc(name);
    glUniform2f(loc, v0, v1);
}

void Shader::setUniform2fv(const char* name, const float* value) {
    int loc = getLoc(name);
    glUniform2fv(loc, 1, value);
}

void Shader::setUniform3fv(const char* name, const float* value) {
    int loc = getLoc(name);
    glUniform3fv(loc, 1, value);
}

void Shader::setUniform4fv(const char* name, const float* value) {
    int loc = getLoc(name);
    glUniform4fv(loc, 1, value);
}

void Shader::setUniformMatrix3fv(const char* name, const float* value) {
    int loc = getLoc(name);
    glUniformMatrix3fv(loc, 1, GL_FALSE, value);
}

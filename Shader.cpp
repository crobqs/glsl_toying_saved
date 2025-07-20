#include "Shader.hpp"

Shader::Shader(const char* vertexShader, const char* fragmentShader) {
    char* fileContent = getFileContent("x.txt");
    printf(fileContent);
    free(fileContent);
}

char* Shader::getFileContent(const char* filename) {
    FILE* f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    int len = ftell(f);
    rewind(f);
    char* fileContent = (char*)calloc(len, 1);
    printf("%d\n", len);
    fread(fileContent, len, len, f);
    fclose(f);
    return fileContent;
}

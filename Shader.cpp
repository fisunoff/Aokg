#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

bool Shader::load(std::string vertexShaderFilename, std::string fragmentShaderFilename) {
    GLuint vertexShader = createShaderObject(GL_VERTEX_SHADER, vertexShaderFilename);
    GLuint fragmentShader = createShaderObject(GL_FRAGMENT_SHADER, fragmentShaderFilename);

    if (vertexShader == 0 || fragmentShader == 0)
        return false;

    // ������� ��������� ���������
    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // �������� �� ������ ��������
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, 512, nullptr, log);
        std::cerr << "������ �������� ��������� ���������:\n" << log << std::endl;
        return false;
    }

    // ����� �������� ����� ������� �������
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

GLuint Shader::createShaderObject(GLenum shaderType, std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "�� ������� ������� ����: " << filename << std::endl;
        return 0;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string code = buffer.str();
    const char* shaderCode = code.c_str();

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, nullptr);
    glCompileShader(shader);

    // �������� �� ������ ����������
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "������ ���������� ������� (" << filename << "):\n" << log << std::endl;
        return 0;
    }

    return shader;
}

void Shader::activate() {
    glUseProgram(program);
}

void Shader::deactivate() {
    glUseProgram(0);
}

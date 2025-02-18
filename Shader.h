#pragma once

#include <string>
#include <GL/glew.h>
#include <gl/GL.h>


// ����� ��� ������ � ��������
class Shader
{
public:
	// �������� ������� �� ������� ������
	bool load(std::string veftexShaderFilename, std::string fragmentShaderFilename);
	// ����� ������� � �������� ��������
	void activate();
	// ���������� �������
	static void deactivate();
private:
	// �������� ���������� ������� ���������� ����
	// � �������� ��������� ������ ������� �� ���������� �����
	GLuint createShaderObject(GLenum shaderType, std::string filename);
private:
	// ��������� ��������� (������)
	GLuint program;
};

#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <memory>
#include <algorithm>

#include "GL/glew.h"
#include <GL/GL.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;
struct Vertex
{
	// �������������� ����������
	vec3 coord;
	// ������ �������
	vec3 normal;
	// ���������� ���������� �������� ����������� ����� 
	vec3 texCoord;
};


class Mesh
{
public:
	// �����������
	Mesh();
	// �������� ���� �� ����� � ��������� ������
	void load(std::string filename);
	// ����� ���� (�������� ���� ������ � OpenGL)
	void draw();
private:
	// ���������� ��������
	int indexCount;
	// ������� (��������������) ������� OpenGL
	GLuint bufferIds[2];
};

#pragma once
#include <iostream>
#include<iomanip>
#include <vector>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <string>
#include <sstream>
#include <map>
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
	// ������ ������ ������������� �����
	vector<Vertex> vertices;
	vector<GLuint> indices;
};

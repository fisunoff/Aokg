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
	// геометрические координаты
	vec3 coord;
	// вектор нормали
	vec3 normal;
	// текстурные координаты нулевого текстурного блока 
	vec3 texCoord;
};


class Mesh
{
public:
	// конструктор
	Mesh();
	// загрузка меша из файла с указанным именем
	void load(std::string filename);
	// вывод меша (передача всех вершин в OpenGL)
	void draw();
private:
	// массив вершин полигональной сетки
	vector<Vertex> vertices;
	vector<GLuint> indices;
};

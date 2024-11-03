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
	// количество индексов
	int indexCount;
	// индексы (идентификаторы) буферов OpenGL
	GLuint bufferIds[2];
};

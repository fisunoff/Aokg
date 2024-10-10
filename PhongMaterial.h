#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;
using namespace std;
// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class PhongMaterial
{
public:
	// конструктор по умолчанию
	PhongMaterial();
	// задание параметров материала
	void setAmbient(vec4 color);
	void setDiffuse(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float p);
	// загрузка параметров материала из внешнего текстового файла
	void load(std::string filename);
	// установка всех параметров материала
	void apply();
private:
	// фоновая составляющая 
	vec4 ambient;
	// диффузная составляющая
	vec4 diffuse;
	// зеркальная составляющая
	vec4 specular;
	// самосвечение
	vec4 emission;
	// степень отполированности
	float shininess;
};
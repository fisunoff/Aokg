#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture.h"
using namespace std;
using namespace glm;

class Material
{
protected:
	vector<vec4> material;
	float shininess;

public:
	Material();
	Material(string sourcePath);
	Material(vec4 diffuse, vec4 ambient, vec4 specular, vec4 emission, float shininess);
	void loadFromFile(string sourcePath);
	void setDiffuse(vec4 color);
	void setAmbient(vec4 color);
	void setSpecular(vec4 color);
	void setEmission(vec4 color);
	void setShininess(float percent);
	virtual void apply() = 0;
};
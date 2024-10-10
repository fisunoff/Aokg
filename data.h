#pragma once
#include <iostream>
#include<iomanip>
#include <vector>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"
#include <fstream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphicObject.h"
#include "camera.h"
#include <string>
#include "light.h"
#include "PhongMaterial.h"
using namespace std;
using namespace glm;

extern vector<GraphicObject> graphicObjects;
extern vector<shared_ptr<PhongMaterial>> materials;

extern Camera camera;
extern GraphicObject obj1;
extern GraphicObject obj2;
extern GraphicObject obj3;
extern GraphicObject obj4;
extern LARGE_INTEGER ticks, ticksPerSecond;
extern Light light;
void init_data();

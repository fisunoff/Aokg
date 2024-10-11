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
#include "Mesh.h"
#include "GameObject.h"
using namespace std;
using namespace glm;

extern vector<GraphicObject> graphicObjects;
extern vector<shared_ptr<PhongMaterial>> materials;

extern Camera camera;

extern LARGE_INTEGER ticks, ticksPerSecond;
extern Light light;

extern vector<shared_ptr<Mesh>> meshes;
extern int passabilityMap[21][21];
// карта проходимости

// список игровых объектов расположенных на карте
extern shared_ptr<GameObject> mapObjects[21][21];
// графический объект для плоскости (частный случай)
extern GraphicObject planeGraphicObject;

void init_data();

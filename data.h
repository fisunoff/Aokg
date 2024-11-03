#pragma once
#include "GL/glew.h"
#include "GameObjectFactory.h"
#include "Camera.h"

#include "GL/freeglut.h"
#include "Light.h"
#include "PhongMaterial.h"
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;
using namespace glm;

extern vector<GraphicObject> graphicObjects;
extern vector<shared_ptr<PhongMaterial>> materials;

extern Camera camera;
extern LARGE_INTEGER ticks, ticksPerSecond, lastChech, currentTime, frequency, StartCounter;
extern Light light;
extern vector<shared_ptr<Mesh>> meshes;
extern int passabilityMap[21][21];
// карта проходимости

// список игровых объектов расположенных на карте
extern shared_ptr<GameObject> mapObjects[21][21];
extern shared_ptr<GameObject> player;
// графический объект для плоскости (частный случай)
extern GraphicObject planeGraphicObject;
extern GameObjectFactory gameObjectFactory;
void initData();

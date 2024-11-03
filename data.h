#pragma once
#include <iostream>
#include<iomanip>
#include <vector>
#include <windows.h>
#include <string>

#include "GL/freeglut.h"
#include <fstream>
#include <memory>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphicObject.h"
#include "Camera.h"
#include "Light.h"
#include "PhongMaterial.h"
#include "Mesh.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
using namespace std;
using namespace glm;

extern vector<GraphicObject> graphicObjects;
extern vector<shared_ptr<PhongMaterial>> materials;

extern Camera camera;
extern LARGE_INTEGER ticks, ticksPerSecond, lastChech, currentTime, frequency;
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

#pragma once
#include "GL/glew.h"
#include "GameObjectFactory.h"
#include "Camera.h"
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include "GL/freeglut.h"
#include "Light.h"
#include "Texture.h"
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
extern Texture planeTexture;
extern Camera camera;
extern LARGE_INTEGER ticks, ticksPerSecond, lastChech, currentTime, frequency, StartCounter;
extern Light light;
extern vector<shared_ptr<Mesh>> meshes;
extern int passabilityMap[21][21];
// ����� ������������
extern shared_ptr<GameObject> enemy[3];
// ������ ������� �������� ������������� �� �����
extern shared_ptr<GameObject> mapObjects[21][21];
extern shared_ptr<GameObject> player;
// ����������� ������ ��� ��������� (������� ������)
extern GraphicObject planeGraphicObject;
extern GameObjectFactory gameObjectFactory;
void initData();

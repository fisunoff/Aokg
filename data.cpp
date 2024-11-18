#include "data.h"

using namespace std;
using namespace glm;

Texture planeTexture;
Camera camera;

LARGE_INTEGER ticks, ticksPerSecond, lastChech, currentTime, frequency, StartCounter;

const int ENEMY_COUNT = 3;

Light light;
int passabilityMap[21][21] = {
 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
 3,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,2,0,0,0,3,
 3,0,2,1,2,0,2,0,2,2,2,1,2,0,2,0,2,0,2,2,3,
 3,0,2,0,2,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,3,
 3,0,1,0,2,2,1,2,2,0,2,0,2,2,2,1,2,0,2,0,3,
 3,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,3,
 3,0,2,2,1,1,2,0,2,0,2,2,2,2,2,0,2,2,2,0,3,
 3,0,2,0,0,0,2,0,2,0,0,0,0,0,2,0,0,0,0,0,3,
 3,0,2,0,2,2,2,0,2,0,2,2,1,2,2,2,1,2,2,0,3,
 3,0,0,0,2,0,0,0,2,0,2,0,0,0,0,0,0,0,1,0,3,
 3,2,2,2,2,0,2,2,2,0,2,0,2,2,2,2,2,2,2,0,3,
 3,0,0,0,2,0,0,0,1,0,2,0,0,0,2,0,0,0,0,0,3,
 3,0,2,0,2,2,2,0,2,1,2,0,2,2,2,0,2,2,2,2,3,
 3,0,2,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,3,
 3,2,2,2,2,0,2,2,2,0,2,2,2,0,1,0,2,2,2,0,3,
 3,0,0,0,0,0,2,0,2,0,0,0,2,0,1,0,0,0,2,0,3,
 3,0,2,0,2,1,2,0,2,0,2,2,2,0,2,2,2,0,2,0,3,
 3,0,1,0,1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,3,
 3,0,2,1,2,0,2,2,2,2,2,0,2,0,2,0,2,2,2,2,3,
 3,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,0,0,0,3,
 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3
};
// список игровых объектов расположенных на карте
shared_ptr<GameObject> mapObjects[21][21];
shared_ptr<GameObject> player;
shared_ptr<GameObject> enemy[ENEMY_COUNT];
// графический объект для плоскости (частный случай)
GraphicObject planeGraphicObject;

// фабрика для создания игровых объектов
GameObjectFactory gameObjectFactory;

void initData() {
	QueryPerformanceCounter(&lastChech);
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&StartCounter);

	camera.setPosition({ 20, 30, 25 });
	light.setDiffuse({ 1,1,1,1 });
	light.setSpecular({ 1,1,1,1 });

	// инициализация фабрики (в дальнейшем на основе json-файла)
	gameObjectFactory.init("data//GameObjectsDescription.json");
	// инициализация объектов сцены
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			switch (passabilityMap[i][j]) {
			case 1:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::LIGHT_OBJECT, i - 10, j - 10);
				break;
			case 2:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::HEAVY_OBJECT, i - 10, j - 10);
				break;
			case 3:
				mapObjects[i][j] = gameObjectFactory.create(GameObjectType::BORDER_OBJECT, i - 10, j - 10);
				break;
			default:
				mapObjects[i][j] = nullptr;
				break;
			}
		}
	}
	// инициализация главного героя
	player = gameObjectFactory.create(GameObjectType::PLAYER, 9, -9);
	for (int i = 0; i < ENEMY_COUNT; i++)
	{
		int xPos = rand() % 21, yPos = rand() % 21;
		while (passabilityMap[xPos][yPos] != 0)
			xPos = rand() % 21, yPos = rand() % 21;
		enemy[i] = gameObjectFactory.create(GameObjectType::ENEMY, xPos - 10, yPos - 10);
		passabilityMap[xPos][yPos] = 4;
	}
	// инициализация плоскости
	planeTexture.load(R"(data\textures\plane.jpg)");
	planeGraphicObject.setPosition(vec3(0, -0.501, 0));
	shared_ptr<Mesh> planeMesh = make_shared<Mesh>();
	planeMesh->load("data\\meshes\\HighPolyPlane.obj");
	planeGraphicObject.setMesh(planeMesh);
	shared_ptr<PhongMaterial> planeMaterial = make_shared<PhongMaterial>();
	planeMaterial->load("data\\materials\\PlaneMaterial.txt");
	planeGraphicObject.setMaterial(planeMaterial);

}
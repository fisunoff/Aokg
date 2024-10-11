#include "data.h"

using namespace std;
using namespace glm;

vector<GraphicObject> graphicObjects;

Camera camera;

LARGE_INTEGER ticks, ticksPerSecond;

GraphicObject obj1;
GraphicObject obj2;
GraphicObject obj3;
GraphicObject obj4;
Light light;
vector<shared_ptr<PhongMaterial>> materials;
vector<shared_ptr<Mesh>> meshes;
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
// графический объект для плоскости (частный случай)
GraphicObject planeGraphicObject;

void init_data() {
	for (int i = 0; i < 4; i++)
	{
		materials.emplace_back(make_shared<PhongMaterial>());
	}
	materials[0]->load("data//materials//material_1.txt");
	materials[1]->load("data//materials//material_2.txt");
	materials[2]->load("data//materials//material_3.txt");
	materials[3]->load("data//materials//material_4.txt");

	for (int i = 0; i < 4; i++)
	{
		meshes.emplace_back(make_shared<Mesh>());
	}
	meshes[0]->load("data//meshes//ChamferBox.obj");
	meshes[1]->load("data//meshes//Box.obj");
	meshes[2]->load("data//meshes//Sphere.obj");
	meshes[3]->load("data//meshes//SimplePlane.obj");

	camera.setPosition({ 20, 30, 25 });
	light.setDiffuse({ 1,1,1,1 });
	light.setSpecular({ 1,1,1,1 });

	planeGraphicObject.setMesh(meshes[3]);
	planeGraphicObject.setMaterial(materials[0]);
	planeGraphicObject.setPosition({ 0,-0.5,0 });

	GraphicObject chambox, graybox, darkbox;
	chambox.setMesh(meshes[0]);
	chambox.setMaterial(materials[1]);

	graybox.setMesh(meshes[1]);
	graybox.setMaterial(materials[2]);

	darkbox.setMesh(meshes[1]);
	darkbox.setMaterial(materials[3]);
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 21; j++)
			if (passabilityMap[i][j])
			{
				mapObjects[i][j] = make_shared<GameObject>();
				mapObjects[i][j]->setPosition(i - 10, j - 10);
				switch (passabilityMap[i][j])
				{
				default: break;
				case 1:
					mapObjects[i][j]->setGraphicObject(chambox); break;
				case 2:
					mapObjects[i][j]->setGraphicObject(graybox); break;
				case 3:
					mapObjects[i][j]->setGraphicObject(darkbox); break;
				}
			}
}
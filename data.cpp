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
vector<std::shared_ptr<PhongMaterial>> materials;

void init_data() {
	for (int i = 0; i < 4; i++)
	{
		materials.emplace_back(std::make_shared<PhongMaterial>());
	}
	materials[0]->load("materials//material_1.txt");
	materials[1]->load("materials//material_2.txt");
	materials[2]->load("materials//material_3.txt");
	materials[3]->load("materials//material_4.txt");

	camera.setPosition({ 10, 15, 17.5 });
	light.setDiffuse({ 64,64,64,1 });
	light.setSpecular({ 64,64,64,1 });
	obj1.setPosition(glm::vec3(4, 0, 0));
	obj1.setAngle(180);
	obj1.set—olor(glm::vec3(1, 0, 0));
	obj1.setMaterial(materials[0]);
	graphicObjects.push_back(obj1);

	obj2.setPosition(glm::vec3(-4, 0, 0));
	obj2.setAngle(0);
	obj2.set—olor(glm::vec3(1, 1, 1));
	obj2.setMaterial(materials[1]);
	graphicObjects.push_back(obj2);

	obj3.setPosition(glm::vec3(0, 0, 4));
	obj3.setAngle(270);
	obj3.set—olor(glm::vec3(0, 1, 0));
	obj3.setMaterial(materials[2]);
	graphicObjects.push_back(obj3);

	obj4.setPosition(glm::vec3(0, 0, -4));
	obj4.setAngle(90);
	obj4.set—olor(glm::vec3(0, 0, 1));
	obj4.setMaterial(materials[3]);
	graphicObjects.push_back(obj4);
}
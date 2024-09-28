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

void init_data() {
	GraphicObject obj1;
	obj1.setPosition(glm::vec3(4, 0, 0));
	obj1.setAngle(180);
	obj1.set—olor(glm::vec3(1, 0, 0));
	graphicObjects.push_back(obj1);

	obj2.setPosition(glm::vec3(-4, 0, 0));
	obj2.setAngle(0);
	obj2.set—olor(glm::vec3(1, 1, 1));
	graphicObjects.push_back(obj2);

	obj3.setPosition(glm::vec3(0, 0, 4));
	obj3.setAngle(270);
	obj3.set—olor(glm::vec3(0, 1, 0));
	graphicObjects.push_back(obj3);

	obj4.setPosition(glm::vec3(0, 0, -4));
	obj4.setAngle(90);
	obj4.set—olor(glm::vec3(0, 0, 1));
	graphicObjects.push_back(obj4);
}
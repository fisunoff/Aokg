#pragma once
#include "data.h"

void simulation();
float getFPS();
void keyboard();
void movePlayer();
void gameObjectsSimulation(float);
void cameraSimulation(float);
void moveEnemy(std::shared_ptr<GameObject>& entity);
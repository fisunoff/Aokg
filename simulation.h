#pragma once
#include "data.h"

void simulation();
float getFPS();
void keyboard();
void movePlayer();
void gameObjectsSimulation(float);
void cameraSimulation(float);
void moveEnemy(std::shared_ptr<GameObject>& entity);
void destroyIfPossible(glm::ivec2 pos, glm::ivec2 displacement, bool Decrease);
void bombSimulation(double currentTime);
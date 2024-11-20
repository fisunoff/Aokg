#include "simulation.h"

float getFPS() {
	long long oldTicks = ticks.LowPart;
	QueryPerformanceCounter(&ticks);
	long long newTicks = ticks.LowPart - oldTicks;
	QueryPerformanceFrequency(&ticksPerSecond);
	float rez = ticksPerSecond.QuadPart / newTicks;
	return rez;
}

void simulation()
{
	static double PrevTime = StartCounter.QuadPart;
	int fps = getFPS();
	QueryPerformanceCounter(&currentTime);
	double deltaTime = (currentTime.QuadPart - PrevTime) / frequency.QuadPart;
	if (currentTime.QuadPart - lastChech.QuadPart >= frequency.QuadPart) {

		glutSetWindowTitle(to_string(fps).c_str());
		QueryPerformanceCounter(&lastChech);
	}
	PrevTime = currentTime.QuadPart;
	cameraSimulation(deltaTime);
	gameObjectsSimulation(deltaTime);

	if (player)
		movePlayer();
	bombSimulation(currentTime.QuadPart);
	for (int i = 0; i < 3; i++)
	{
		if (enemy[i])
			moveEnemy(enemy[i]);
	}

	glutPostRedisplay();

};

void movePlayer()
{
	static struct { int key, x1, y1, x2, y2; MoveDirection dir; }
	Moves[4]
	{
		{0x41,9,10,8,10,MoveDirection::LEFT},
		{0x44,11,10,12,10,MoveDirection::RIGHT},
		{0x57,10,9,10,8,MoveDirection::UP},
		{0x53,10,11,10,12,MoveDirection::DOWN}
	};
	ivec2 playerPos = player->getPosition();
	if (passabilityMap[playerPos.x + 10][playerPos.y + 10] == 4)
	{
		player.reset();
		system("cls");
		return;
	}
	for (auto move : Moves)
	{
		if (static_cast<bool>(GetAsyncKeyState(move.key)) && !player->isMoving() && passabilityMap[playerPos.x + move.x1][playerPos.y + move.y1] <= 1)
		{
			if (passabilityMap[playerPos.x + move.x1][playerPos.y + move.y1] == 1 && passabilityMap[playerPos.x + move.x2][playerPos.y + move.y2] == 0)
			{
				mapObjects[playerPos.x + move.x1][playerPos.y + move.y1]->move(move.dir, 2);
				player->move(move.dir, 2);
				swap(passabilityMap[playerPos.x + move.x1][playerPos.y + move.y1], passabilityMap[playerPos.x + move.x2][playerPos.y + move.y2]);
				swap(mapObjects[playerPos.x + move.x1][playerPos.y + move.y1], mapObjects[playerPos.x + move.x2][playerPos.y + move.y2]);
			}
			else if (passabilityMap[playerPos.x + move.x1][playerPos.y + move.y1] == 0)
			{
				player->move(move.dir);
			}
		}
	}
}
void cameraSimulation(float deltaTime)
{
	static float rotateSpeed = 180.0;
	static float leanSpeed = 1.f;
	int keyLeft = GetAsyncKeyState(VK_LEFT);
	int keyRight = GetAsyncKeyState(VK_RIGHT);
	int keyUp = GetAsyncKeyState(VK_UP);
	int keyDown = GetAsyncKeyState(VK_DOWN);
	int keyPlus = GetAsyncKeyState(VK_ADD);
	int keySub = GetAsyncKeyState(VK_SUBTRACT);
	// для провекри класса камеры вызываем методы передвижения
	if (keyUp & 0x01)
	{
		camera.rotateUpDown(rotateSpeed * deltaTime);
		return;
	}
	if (keyDown & 0x01)
	{
		camera.rotateUpDown(-rotateSpeed * deltaTime);
		return;
	}
	if (keyRight & 0x01)
	{
		camera.rotateLeftRight(-rotateSpeed * deltaTime);
		return;
	}
	if (keyLeft & 0x01)
	{
		camera.rotateLeftRight(rotateSpeed * deltaTime);
		return;
	}
	if (keyPlus & 0x01)
	{
		camera.zoomInOut(-40 * deltaTime);
		return;
	}
	if (keySub & 0x01)
	{
		camera.zoomInOut(40 * deltaTime);
		return;
	}

	return;
}
void gameObjectsSimulation(float deltaTime)
{
	if (player)
		player->simulate(deltaTime);
	for (auto& i : mapObjects)
		for (auto& j : i)
			if (j != nullptr)j->simulate(deltaTime);
	for (auto& i : enemy)
		if (i)
			i->simulate(deltaTime);

}
void killPlayer()
{
	player.reset();
	system("cls");
}
void destroyIfPossible(glm::ivec2 pos, glm::ivec2 displacement, bool Decrease)
{
	if (Decrease) displacement *= -1;

	if (player)
	{
		glm::ivec2 realPos{ pos.x - 10,pos.y - 10 };
		glm::ivec2 playerPos = player->getPosition();
		if ((glm::ivec2({ realPos.x + displacement.x,realPos.y + displacement.y }) == playerPos && passabilityMap[pos.x][pos.y] == 0)
			|| glm::ivec2({ realPos.x,realPos.y }) == playerPos)
		{
			killPlayer();
			return;
		}
	}

	if (passabilityMap[pos.x][pos.y] == 1 || passabilityMap[pos.x][pos.y] == 4)
	{
		for (int i = 0; i < 3; i++)
			if (enemy[i] && enemy[i] == mapObjects[pos.x][pos.y])
			{
				enemy[i].reset();
				break;
			}
		mapObjects[pos.x][pos.y].reset();
		passabilityMap[pos.x][pos.y] = 0;
		return;
	}
	if (passabilityMap[pos.x][pos.y] == 0 &&
		(passabilityMap[pos.x + displacement.x][pos.y + displacement.y] == 1 || passabilityMap[pos.x + displacement.x][pos.y + displacement.y] == 4))
	{
		for (int i = 0; i < 3; i++)
			if (enemy[i] && enemy[i] == mapObjects[pos.x + displacement.x][pos.y + displacement.y])
			{
				enemy[i].reset();
				break;
			}
		mapObjects[pos.x + displacement.x][pos.y + displacement.y].reset();
		passabilityMap[pos.x + displacement.x][pos.y + displacement.y] = 0;
	}
	return;
}
void bombSimulation(double currentTime)
{
	static double timeToActivate = 2.0 * frequency.QuadPart;
	static LARGE_INTEGER placementTime;
	static ivec2 bombPos;
	static bool isBombSet = false;
	if (player && !isBombSet && (GetAsyncKeyState(VK_SPACE)) & 0x8000)
	{
		isBombSet = true;
		QueryPerformanceCounter(&placementTime);
		bombPos = { player->getPosition().x + 10, player->getPosition().y + 10 };
		mapObjects[bombPos.x][bombPos.y] = gameObjectFactory.create(GameObjectType::BOMB, bombPos - 10);
		passabilityMap[bombPos.x][bombPos.y] = 5;
	}

	if (isBombSet && currentTime - placementTime.QuadPart >= timeToActivate)
	{
		isBombSet = false;
		mapObjects[bombPos.x][bombPos.y].reset();
		passabilityMap[bombPos.x][bombPos.y] = 0;


		destroyIfPossible({ bombPos.x - 1,bombPos.y }, { 1,0 }, true);
		destroyIfPossible({ bombPos.x + 1,bombPos.y }, { 1,0 }, false);
		destroyIfPossible({ bombPos.x, bombPos.y - 1 }, { 0,1 }, true);
		destroyIfPossible({ bombPos.x, bombPos.y + 1 }, { 0,1 }, false);
	}

}


void moveEnemy(shared_ptr<GameObject>& entity)
{
	static struct { int key, x1, y1, x2, y2; MoveDirection dir; }
	Moves[4]
	{
		{0,9,10,8,10,MoveDirection::LEFT},
		{1,11,10,12,10,MoveDirection::RIGHT},
		{2,10,9,10,8,MoveDirection::UP},
		{3,10,11,10,12,MoveDirection::DOWN}
	};
	ivec2 entityPos = entity->getPosition();
	int PickMove = entity->getLastDir();
	if (!entity->isMoving() && passabilityMap[entityPos.x + Moves[PickMove].x1][entityPos.y + Moves[PickMove].y1] == 0)
	{
		entity->move(Moves[PickMove].dir, 1);
		swap(passabilityMap[entityPos.x + Moves[PickMove].x1][entityPos.y + Moves[PickMove].y1],
			passabilityMap[entityPos.x + 10][entityPos.y + 10]);
		swap(mapObjects[entityPos.x + Moves[PickMove].x1][entityPos.y + Moves[PickMove].y1],
			mapObjects[entityPos.x + 10][entityPos.y + 10]);
	}

}

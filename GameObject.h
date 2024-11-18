#pragma once
#include "GL/glew.h"
#include "graphicObject.h"
#include <fstream>
#include<iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>
enum class  MoveDirection { STOP, LEFT, RIGHT, UP, DOWN };
class GameObject
{
public:
	// конструктор
	GameObject();
	// установка используемого графического объекта
	// происходит копирование переданного объекта дл€ последующего использовани€
	void setGraphicObject(const GraphicObject& graphicObject);
	// установка логических координат (два перегруженных метода дл€ удобства)
	void setPosition(int x, int y);
	void setPosition(ivec2 position);
	// получение текущих логических координат
	ivec2 getPosition();

	// начать движение в выбранном направлении с указанной скоростью
// скорость передвижени€ определ€етс€ количеством клеток в секунду
	void move(MoveDirection direction, float speed = 3.0f);
	// проверка на то, что объект в насто€щий момент движетс€
	bool isMoving();
	// симул€ци€ игрового объекта (плавное перемещение объекта)
	// метод вызываетс€ непрерывно в функции simulation
	void simulate(float sec);
	int getLastDir();
	// вывод игрового объекта на экран
	void draw(void);
private:
	// графический объект (дл€ вывода на экран)
	GraphicObject graphicObject;
	// логические координаты игрового объекта
	ivec2 position;
	// состо€ние объекта (заданное направление перемещени€)
	MoveDirection sost, lastdir;
	// прогресс в перемещении (от 0.0 до 1.0)
	float progress;
	// скорость перемещени€
	float speed;

};

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
	// �����������
	GameObject();
	// ��������� ������������� ������������ �������
	// ���������� ����������� ����������� ������� ��� ������������ �������������
	void setGraphicObject(const GraphicObject& graphicObject);
	// ��������� ���������� ��������� (��� ������������� ������ ��� ��������)
	void setPosition(int x, int y);
	void setPosition(ivec2 position);
	// ��������� ������� ���������� ���������
	ivec2 getPosition();

	// ������ �������� � ��������� ����������� � ��������� ���������
// �������� ������������ ������������ ����������� ������ � �������
	void move(MoveDirection direction, float speed = 3.0f);
	// �������� �� ��, ��� ������ � ��������� ������ ��������
	bool isMoving();
	// ��������� �������� ������� (������� ����������� �������)
	// ����� ���������� ���������� � ������� simulation
	void simulate(float sec);
	int getLastDir();
	// ����� �������� ������� �� �����
	void draw(void);
private:
	// ����������� ������ (��� ������ �� �����)
	GraphicObject graphicObject;
	// ���������� ���������� �������� �������
	ivec2 position;
	// ��������� ������� (�������� ����������� �����������)
	MoveDirection sost, lastdir;
	// �������� � ����������� (�� 0.0 �� 1.0)
	float progress;
	// �������� �����������
	float speed;

};

#pragma once
#include "GL/freeglut.h"
#include "graphicObject.h"
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
	// ����� �������� ������� �� �����
	void draw(void);
private:
	// ���������� ���������� �������� �������
	ivec2 position;
	// ����������� ������ (��� ������ �� �����)
	GraphicObject graphicObject;
};

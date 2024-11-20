#pragma once
#include <windows.h> //Required for RapidJSON

#include "Mesh.h"

#include "PhongMaterialWithTexture.h"
#include "GraphicObject.h"
#include "PhongMaterial.h"

#include "GameObject.h"
#include "rapidjson/document.h"
using namespace rapidjson;

// ����������� ����� ������� ��������
enum GameObjectType {
	LIGHT_OBJECT, // ������ ������� ������
	HEAVY_OBJECT, // ������� ������� ������
	BORDER_OBJECT, // ��������� ������� ������
	PLAYER, // ������� ������ ��� ������������� ������
	ENEMY,// ������� ������ ��� ������������� ��������
	BOMB, // ������� ������ ��� ������������� �����
};

// ����� ��� �������� ������� ��������
class GameObjectFactory
{
public:
	// ������������� �������:
	// �������� ����� � ��������� ���������� ���������
	bool init(string filename);
	// �������� ������ ������� ��������� ����
	shared_ptr<GameObject> create(GameObjectType type, int x, int y);
	shared_ptr<GameObject> create(GameObjectType type, vec2 pos);
private:
	// ���� ��� ������� ���� �������
	vector<shared_ptr<Mesh>> meshes;
	// ��������� ��� ������� ���� �������
	vector<shared_ptr<Material>> materials;
};


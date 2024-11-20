#pragma once
#include <windows.h> //Required for RapidJSON

#include "Mesh.h"

#include "PhongMaterialWithTexture.h"
#include "GraphicObject.h"
#include "PhongMaterial.h"

#include "GameObject.h"
#include "rapidjson/document.h"
using namespace rapidjson;

// ОПРЕДЕЛЕНИЕ ТИПОВ ИГРОВЫХ ОБЪЕКТОВ
enum GameObjectType {
	LIGHT_OBJECT, // легкий игровой объект
	HEAVY_OBJECT, // тяжелый игровой объект
	BORDER_OBJECT, // граничный игровой объект
	PLAYER, // игровой объект для представления игрока
	ENEMY,// игровой объект для представления монстров
	BOMB, // игровой объект для представления бомбы
};

// КЛАСС ДЛЯ СОЗДАНИЯ ИГРОВЫХ ОБЪЕКТОВ
class GameObjectFactory
{
public:
	// инициализация фабрики:
	// загрузка мешей и установка параметров материала
	bool init(string filename);
	// создание нового объекта заданного типа
	shared_ptr<GameObject> create(GameObjectType type, int x, int y);
	shared_ptr<GameObject> create(GameObjectType type, vec2 pos);
private:
	// меши для каждого типа объекта
	vector<shared_ptr<Mesh>> meshes;
	// материалы для каждого типа объекта
	vector<shared_ptr<Material>> materials;
};


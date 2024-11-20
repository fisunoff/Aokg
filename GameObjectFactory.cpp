#include "GameObjectFactory.h"
bool GameObjectFactory::init(string path)
{
	ifstream file(path);

	if (!file)
	{
		return false;
	}

	string jsonString;
	getline(file, jsonString, static_cast<char>(0));
	file.close();
	Document jsonFile;
	jsonFile.Parse(jsonString.c_str());


	if (jsonFile.GetParseError() != 0)
	{
		return false;
	}
	// перебор всех ключей в записи и вывод пар [ключ : значение],
// если значение является строкой
	// перебор всех ключей в записи и вывод пар [ключ : значение],
// если значение является строкой
	for (auto itr = jsonFile.MemberBegin(); itr != jsonFile.MemberEnd(); ++itr) {
		Mesh mesh;

		(jsonFile[itr->name].HasMember("texture")) ?
			materials.emplace_back(std::make_shared<PhongMaterialWithTexture>(jsonFile[itr->name]["texture"].GetString(), 0))
			:
			materials.emplace_back(std::make_shared<PhongMaterial>());

		mesh.load(jsonFile[itr->name.GetString()]["mesh"].GetString());
		meshes.emplace_back(make_shared<Mesh>(mesh));

		auto tempArr = jsonFile[itr->name.GetString()]["material"]["diffuse"].GetArray();
		materials.back()->setDiffuse({ tempArr[0].GetDouble(),tempArr[1].GetDouble() ,tempArr[2].GetDouble() ,tempArr[3].GetDouble() });

		tempArr = jsonFile[itr->name.GetString()]["material"]["ambient"].GetArray();
		materials.back()->setAmbient({ tempArr[0].GetDouble(),tempArr[1].GetDouble() ,tempArr[2].GetDouble() ,tempArr[3].GetDouble() });

		tempArr = jsonFile[itr->name.GetString()]["material"]["specular"].GetArray();
		materials.back()->setSpecular({ tempArr[0].GetDouble(),tempArr[1].GetDouble() ,tempArr[2].GetDouble() ,tempArr[3].GetDouble() });

		tempArr = jsonFile[itr->name.GetString()]["material"]["emission"].GetArray();
		materials.back()->setEmission({ tempArr[0].GetDouble(),tempArr[1].GetDouble() ,tempArr[2].GetDouble() ,tempArr[3].GetDouble() });

		materials.back()->setShininess(jsonFile[itr->name.GetString()]["material"]["shininess"].GetDouble());
	}



	return true;
};

shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, int x, int y)
{
	shared_ptr<GameObject> newObject = make_shared<GameObject>();
	GraphicObject gf;
	gf.setMesh(meshes[type]);
	gf.setMaterial(materials[type]);
	newObject->setPosition(x, y);
	newObject->setGraphicObject(gf);
	return newObject;

}
shared_ptr<GameObject> GameObjectFactory::create(GameObjectType type, glm::vec2 pos)
{
	std::shared_ptr<GameObject> newObject = std::make_shared<GameObject>();
	GraphicObject graphObj;
	graphObj.setMesh(meshes[type]);
	graphObj.setMaterial(materials[type]);
	newObject->setPosition(pos);
	newObject->setGraphicObject(graphObj);
	return newObject;
}
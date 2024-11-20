#include "Material.h"

Material::Material()
{
	this->material.push_back(vec4(.8, .8, .8, 1)); //diffuse
	this->material.push_back(vec4(.2, .2, .2, 1)); //ambient
	this->material.push_back(vec4(.0, .0, .0, 1)); //specular
	this->material.push_back(vec4(.0, .0, .0, 1)); //emission
	this->shininess = .0;
}
Material::Material(vec4 diffuse, vec4 ambient, vec4 specular, vec4 emission, float shininess)
{
	this->material.push_back(diffuse);
	this->material.push_back(ambient);
	this->material.push_back(specular);
	this->material.push_back(emission);
	this->shininess = shininess;
}
Material::Material(string sourcePath)
{
	this->material = vector<vec4>(4);
	this->loadFromFile(sourcePath);
}

void Material::setDiffuse(vec4 color)
{
	this->material[0] = color;
};
void Material::setAmbient(vec4 color)
{
	this->material[1] = color;
};
void Material::setSpecular(vec4 color)
{
	this->material[2] = color;
};
void Material::setEmission(vec4 color)
{
	this->material[3] = color;
};
void Material::setShininess(float amount)
{
	this->shininess = fmod(amount, 128.01);
};

void Material::loadFromFile(string sourcePath)
{
	ifstream File(sourcePath);
	if (!File)
	{
		cerr << "\nFailed to load from " << sourcePath;
		return;
	}
	string currentFieldName;
	for (int j = 0; j < 4; j++)
	{
		File >> currentFieldName;
		cout << currentFieldName << ' ';
		for (int i = 0; i < 4; i++)
		{
			File >> (this->material[j])[i];
		}
	}
	File >> currentFieldName;
	File >> this->shininess;
	cout << currentFieldName << ' ' << this->shininess << endl;
}

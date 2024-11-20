#pragma once
#include "Material.h"

class PhongMaterialWithTexture final : public Material
{
private:
	shared_ptr<Texture> texture;
public:
	PhongMaterialWithTexture();
	PhongMaterialWithTexture(string sourcePath);
	PhongMaterialWithTexture(string textureSourcePath, int);
	PhongMaterialWithTexture(string materialSourcePath, string textureSourcePath);
	PhongMaterialWithTexture(string materialSourcePath, shared_ptr<Texture> sharedTex);

	void setTexture(shared_ptr<Texture> texture);
	void apply();
};
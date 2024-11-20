#pragma once
#include "Material.h"

class PhongMaterial final : public Material
{
public:
	PhongMaterial();
	PhongMaterial(string sourcePath);
	void apply();
};
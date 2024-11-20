#include "PhongMaterial.h"

PhongMaterial::PhongMaterial() :Material() {};
PhongMaterial::PhongMaterial(string sourcePath) :Material(sourcePath) {}


void PhongMaterial::apply()
{
	Texture::disableAll();
	glMaterialfv(GL_FRONT, GL_DIFFUSE, value_ptr(this->material[0]));
	glMaterialfv(GL_FRONT, GL_AMBIENT, value_ptr(this->material[1]));
	glMaterialfv(GL_FRONT, GL_SPECULAR, value_ptr(this->material[2]));
	glMaterialfv(GL_FRONT, GL_EMISSION, value_ptr(this->material[3]));
	glMaterialf(GL_FRONT, GL_SHININESS, this->shininess);
}
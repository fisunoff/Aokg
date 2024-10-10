#include "PhongMaterial.h"
PhongMaterial::PhongMaterial() {
	ambient = { 0.0,0.0,0.0,1 };
	diffuse = { 0.0,0.0,0.0,1 };
	specular = { 0.0,0.0,0.0,1 };
	emission = { 0.0,0.0,0.0,1 };
	shininess =0.0;
}
void PhongMaterial::setAmbient(vec4 color) {
	ambient = color;
}
void PhongMaterial::setDiffuse(vec4 color) {
	diffuse = color;
}
void PhongMaterial::setSpecular(vec4 color) {
	specular = color;
}
void PhongMaterial::setEmission(vec4 color) {
	emission = color;
}
void PhongMaterial::setShininess(float p) {
	shininess = p;
}
void PhongMaterial::load(string filename) {
	ifstream reader(filename);
	if (!reader)
	{
		std::cerr << "\nFailed to load from " << filename;
		return;
	}
	string name;
	reader >> name;
	for (int i = 0; i < 4; i++)
	{
		reader >> diffuse[i];
	}
	reader >> name;
	for (int i = 0; i < 4; i++)
	{
		reader >> ambient[i];
	}
	reader >> name;
	for (int i = 0; i < 4; i++)
	{
		reader >> specular[i];
	}
	reader >> name;
	for (int i = 0; i < 4; i++)
	{
		reader >> emission[i];
	}
	reader >> name;
	reader >> shininess;
}
// применение материала
void PhongMaterial::apply(void)
{
	glMaterialfv(GL_FRONT, GL_DIFFUSE, value_ptr(diffuse));
	glMaterialfv(GL_FRONT, GL_AMBIENT, value_ptr(ambient));
	glMaterialfv(GL_FRONT, GL_SPECULAR, value_ptr(specular));
	glMaterialfv(GL_FRONT, GL_EMISSION, value_ptr(emission));
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}
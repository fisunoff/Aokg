#include "Light.h"

Light::Light() {
	position = { 10, 10, 10, 1 };
	ambient = { 0.2, 0.2, 0.2, 1.0 };
	diffuse = { 0,0,0,1 };
	specular = { 0,0,0,1 };

}
Light::Light(vec3 position) {
	this->position = { position.x, position.y, position.z, 1 };
	ambient = { 0.2, 0.2, 0.2, 1.0 };
	diffuse = { 0,0,0,0 };
	specular = { 0,0,0,0 };
}
Light::Light(float x, float y, float z) {
	position = { x,y,z,1 };
	ambient = { 0.2, 0.2, 0.2, 1.0 };
	diffuse = { 0,0,0,0 };
	specular = { 0,0,0,0 };
}

void Light::setPosition(vec3 position) {
	this->position = { position.x, position.y, position.z, 1 };
}

void Light::setAmbient(vec4 color) {
	ambient = color;
}
void Light::setDiffuse(vec4 color) {
	diffuse = color;
}
void Light::setSpecular(vec4 color) {
	specular = color;
}
void Light::apply(GLenum LightNumber = GL_LIGHT0) {
	//GLfloat globalAmbientColor[] = { 0.2, 0.2, 0.2, 1.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientColor);
	glLightfv(LightNumber, GL_AMBIENT, value_ptr(ambient));
	glLightfv(LightNumber, GL_DIFFUSE, value_ptr(diffuse));
	glLightfv(LightNumber, GL_SPECULAR, value_ptr(specular));
	glLightfv(LightNumber, GL_POSITION, value_ptr(position));
	glEnable(LightNumber);
}
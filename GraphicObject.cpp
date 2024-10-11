#include "GraphicObject.h"
GraphicObject::GraphicObject()
{
	angle = 0;
	position = { 0,0,0 };
	color = { 1,1,1 };
	modelMatrix = { 
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
	axis = { 0, 1, 0 }; // задаем ось вращения - Y
	material = nullptr;
	this->mesh = nullptr;
}
void GraphicObject::setPosition(vec3 position)
{
	this->position = position;
	recalculateModelMatrix();
}
vec3 GraphicObject::getPosition()
{
	return position;
}
void GraphicObject::setAngle(float grad)
{
	this->angle = grad;
	recalculateModelMatrix();
}
float GraphicObject::getAngle()
{
	return angle;
}
void GraphicObject::setСolor(vec3 color)
{
	this->color = color;
}
vec3 GraphicObject::getColor()
{
	return color;
}
void GraphicObject::setMaterial(shared_ptr<PhongMaterial> material)
{
	this->material = material;
}
// расчет матрицы modelMatrix на основе position и angle
void GraphicObject::recalculateModelMatrix()
{
	modelMatrix = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
	modelMatrix = translate(modelMatrix, position);
	modelMatrix = rotate(modelMatrix, radians(-angle), vec3(0, 1, 0));
}

void GraphicObject::setMesh(shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}
// вывести объект
void GraphicObject::draw()
{
	glColor3f(color.r, color.g, color.b);
	if (material != nullptr) {
		material->apply();
	}
	glPushMatrix();
	glMultMatrixf((GLfloat*)&modelMatrix);
	if (this->mesh != nullptr)
		this->mesh->draw();
	glPopMatrix();
}
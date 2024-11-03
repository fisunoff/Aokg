#include "GraphicObject.h"
GraphicObject::GraphicObject()
{
	this->angle = 0;
	this->position = { 0,0,0 };
	this->color = { 1,1,1 };
	this->modelMatrix = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
	this->material = nullptr;
	this->mesh = nullptr;
}
void GraphicObject::setPosition(vec3 position)
{
	this->position[0] = position[0];
	this->position[1] = position[1];
	this->position[2] = position[2];
	recalculateModelMatrix();
}
vec3 GraphicObject::getPosition()
{
	vec3 temp = { 0,0,0 };
	temp[0] = this->position[0];
	temp[1] = this->position[1];
	temp[2] = this->position[2];
	return temp;
}
void GraphicObject::setAngle(float grad)
{
	this->angle = grad;
	recalculateModelMatrix();
}
float GraphicObject::getAngle()
{
	return this->angle;
}
void GraphicObject::set�olor(vec3 color)
{
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
}
vec3 GraphicObject::getColor()
{
	vec3 temp = { 0,0,0 };
	temp[0] = this->color[0];
	temp[1] = this->color[1];
	temp[2] = this->color[2];
	return temp;
}
void GraphicObject::setMaterial(shared_ptr<PhongMaterial> material)
{
	this->material = material;
}
// ������ ������� modelMatrix �� ������ position � angle
void GraphicObject::recalculateModelMatrix()
{
	this->modelMatrix = {
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
	modelMatrix = translate(modelMatrix, position);
	modelMatrix = rotate(modelMatrix, radians(-angle), vec3(0, 1, 0));

}
// ������� ������
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
void GraphicObject::setMesh(shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}
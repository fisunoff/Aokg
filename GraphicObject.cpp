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
	axis = { 0, 1, 0 }; // ������ ��� �������� - Y
}
void GraphicObject::setPosition(vec3 position)
{
	this->position = position;
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
void GraphicObject::set�olor(vec3 color)
{
	this->color = color;
}
vec3 GraphicObject::getColor()
{
	return color;
}
// ������ ������� modelMatrix �� ������ position � angle
void GraphicObject::recalculateModelMatrix()
{
	modelMatrix = translate(modelMatrix, position);
	modelMatrix = rotate(modelMatrix, radians(-angle), axis);
}
// ������� ������
void GraphicObject::draw()
{
	glColor3f(color.r, color.g, color.b);
	glPushMatrix();
	glMultMatrixf((GLfloat*)&modelMatrix);
	glutWireTeapot(1.0);
	glPopMatrix();
}
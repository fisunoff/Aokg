#include "GameObject.h"

GameObject::GameObject() {
	this->sost = MoveDirection::STOP;
	this->speed = 3.0f;
	this->progress = 0.0f;
	this->setPosition({ 0,0 });
}

void GameObject::setGraphicObject(const GraphicObject& graphicObject) {
	this->graphicObject = graphicObject;
	this->graphicObject.setPosition({ position.x,0,position.y });
}
void GameObject::setPosition(int x, int y) {
	position = { x,y };
}
void GameObject::setPosition(ivec2 position) {
	this->position = position;
}
ivec2 GameObject::getPosition() {
	return position;
}
void GameObject::draw() {
	graphicObject.draw();
}
void GameObject::move(MoveDirection direction, float speed)
{
	if (this->isMoving()) return;
	this->progress = 0.0;
	this->sost = direction;
	this->speed = speed;
}
void GameObject::simulate(float sec)
{
	if (this->sost == MoveDirection::STOP) return;
	glm::vec3 pos = this->graphicObject.getPosition();
	glm::ivec2 playerPos = this->getPosition();
	if (this->progress > 1.0)
	{
		this->sost = MoveDirection::STOP;
		this->setPosition(round(this->graphicObject.getPosition().x), round(this->graphicObject.getPosition().z));
		return;
	}
	switch (this->sost)
	{
	case MoveDirection::LEFT:
		this->graphicObject.setPosition({ playerPos.x * (1 - this->progress) + (playerPos.x - 1) * (this->progress),pos.y, pos.z });
		break;
	case MoveDirection::RIGHT:
		this->graphicObject.setPosition({ playerPos.x * (1 - this->progress) + (playerPos.x + 1) * (this->progress),pos.y, pos.z });
		break;
	case MoveDirection::UP:
		this->graphicObject.setPosition({ pos.x,pos.y, playerPos.y * (1 - this->progress) + (playerPos.y - 1) * (this->progress) });
		break;
	case MoveDirection::DOWN:
		this->graphicObject.setPosition({ pos.x,pos.y, playerPos.y * (1 - this->progress) + (playerPos.y + 1) * (this->progress) });
		break;
	}
	this->progress += this->speed * sec;
}
bool GameObject::isMoving()
{
	return this->sost != MoveDirection::STOP;
}
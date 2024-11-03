#include "Camera.h"

// установка позиции камеры
void Camera::setPosition(vec3 position)
{
	// определяем радиус - расстояние от начала системы координат до заданной позиции
	r = length(position);
	// определяем вертикальный угол:
	// это угол между вектором из начала координат к наблюдателю (v1)
	// и проекцией этого вектора на горизонтальную плоскость (v2)
	// для определения угла используется скалярное произведение нормализованных векторов 
	vec3 v1 = position;
	vec3 v2 = vec3(v1.x, 0, v1.z);
	float cos_y = dot(normalize(v1), normalize(v2));
	angleY = degrees(acos(cos_y));
	// аналогичным образом определяем горизонтальный угол:
	// это угол между проекцией (v2) и единичным вектором вдоль оси Ox
	float cos_x = dot(normalize(v2), vec3(1, 0, 0));
	angleX = degrees(acos(cos_x));
	// пересчитываем позицию (для корректировок ошибок округления)
	recalculatePosition();
}
Camera::Camera() {
	position = { 0, 0, 0 };
	vec3 new_position = { 10.0, 15.0, 17.5 };
	setPosition(new_position);
}
Camera::Camera(vec3 pos) {
	position = { 0, 0, 0 };
	setPosition(pos);
}
Camera::Camera(GLfloat x, GLfloat y, GLfloat z) {
	position = { 0, 0, 0 };
	vec3 new_position = { x, y, z };
	setPosition(new_position);
}

vec3 Camera::getPosition() {
	return position;
}

void Camera::apply() {
	gluLookAt(position.x, position.y, position.z, 0, 0, 0, 0, 1, 0);
}

void Camera::recalculatePosition() {
	position.x = r * sin(radians(90 - angleY)) * cos(radians(angleX));
	position.y = r * cos(radians(90 - angleY));
	position.z = r * sin(radians(90 - angleY)) * sin(radians(angleX));
}
void Camera::rotateLeftRight(float degree) {
	angleX += degree;
	recalculatePosition();
}
void Camera::rotateUpDown(float degree) {
	if (degree < 0 and angleY < -45)  // защита от переворота
		return;
	if (degree > 0 and angleY > 85)  // защита от переворота
		return;
	angleY += degree;
	recalculatePosition();
}

void Camera::zoomInOut(float distance) {
	r -= distance;
	recalculatePosition();
}
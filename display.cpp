#include "display.h"

void drawPlane()
{
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	planeGraphicObject.draw();
	Texture::disableAll();
}
// �������, ���������� ��� ��������� �������� ����
void reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, GLsizei(w), GLsizei(h));
	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, GLfloat(w) / h, 0.2, 70.0);
};

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void display(void)
{
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	// ������������� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.apply();
	// ������������� �������� �����
	light.apply(GL_LIGHT0);
	drawPlane();
	if (player)
		player->draw();
	for (auto& i : mapObjects)
		for (auto& j : i)
			if (j != nullptr) j->draw();

	// ����� ��������� � ������� �������
	glutSwapBuffers();
};
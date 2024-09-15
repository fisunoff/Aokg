#include <windows.h>

#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// ���������� ������������ ���� ����������� ����������
using namespace std;
using namespace glm;

#define CHANGE_TIME_MS 1000

int index = 0;
int timer;
vec3 black = { 0.0f, 0.0f, 0.0f };
vec3 white = { 1.0f, 1.0f, 1.0f };
vec3 blue = { 0.0f, 0.0f, 1.0f };
vec3 red = { 1.0f, 0.0f, 0.0f };
vec3 violet = { 1.0f, 0.0f, 1.0f };

vector<vec3> colors = { black, white, blue, red, violet };
int max_index = colors.size();


// �������, ���������� ��� ��������� �������� ����
void reshape(int w, int h)
{
	// ���������� ����� ������� ���������, ������ ���� ������� ����
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// ���������� ������� �������� � ���������� ��������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// ������� ���������� ��� ����������� ����
// � ��� ����� � �������������, �� �������� glutPostRedisplay
void display(void)
{
	// �������� ����� ����� � ����� �������
	glClearColor(0.2, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �������� ���� �������
	glEnable(GL_DEPTH_TEST);

	// ������������� ������
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);

	// ������� ������ - ������� (1,0,0) ������
	auto color_now = colors[index];
	glColor3f(color_now[0], color_now[1], color_now[2]);
	glutWireTeapot(1.0);

	// ����� ��������� � ������� �������
	glutSwapBuffers();
};

void change_color() {
	// ����� ����� �� ������� ������ CHANGE_TIME_MS ��
	index = (index + 1) % max_index; // ������� ������ �� ���������, ����������
	cout << "Changed color to " << colors[index][0] << " " << colors[index][1] << " " << colors[index][2] << endl;
}

// ������� ���������� ������ 20 ��
void simulation(int value)
{
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
	// ��� �� ������� ����� ������� ��� ��� ����� 20 ��
	glutTimerFunc(20, simulation, 0);
	timer += 20;
	if (timer >= CHANGE_TIME_MS) { // ���� ������ CHANGE_TIME_MS, �� ������ ���� � ��������� timer
		change_color();
		timer -= CHANGE_TIME_MS;
	}
};

// ������� ��������� ������� ������
void keyboardFunc(unsigned char key, int x, int y)
{
	change_color();
	printf("Key code is %i\n Color changed\n", key);
};

void main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");

	// ������������� ���������� GLUT
	glutInit(&argc, argv);
	// ������������� ������� (������ ������)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// �������� ����:
	// 1. ������������� ������� ����� ���� ����
	glutInitWindowPosition(200, 200);
	// 2. ������������� ������ ����
	glutInitWindowSize(800, 600);
	// 3. ������� ����
	glutCreateWindow("Laba_01");

	// ��������� ������� ��������� ������
	// ������������� �������, ������� ����� ���������� ��� ����������� ����
	glutDisplayFunc(display);
	// ������������� �������, ������� ����� ���������� ��� ��������� �������� ����
	glutReshapeFunc(reshape);
	// ������������� �������, ������� ����� ������� ����� 20 ��
	glutTimerFunc(20, simulation, 0);
	// ������������� �������, ������� ����� ���������� ��� ������� �� �������
	glutKeyboardFunc(keyboardFunc);

	// �������� ���� ��������� ��������� ��
	glutMainLoop();
};
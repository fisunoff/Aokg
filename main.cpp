#include <windows.h>

#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

// ���������� ������������ ���� ����������� ����������
using namespace std;

#define CHANGE_TIME_MS 2000

int index = 0;
vector<double> black = { 0, 0, 0 };
vector<double> white = { 1, 1, 1 };
vector<double> blue = { 0, 0, 1 };
vector<double> red = { 1, 0, 0 };
vector<double> violet = { 1, 0, 1 };

vector< vector<double>> colors = { black, white, blue, red, violet };
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

// ������� ���������� ������ 20 ��
void simulation(int value)
{
	// ������������� ������� ����, ��� ���� ��������� � �����������
	glutPostRedisplay();
	// ��� �� ������� ����� ������� ��� ��� ����� 20 ��
	glutTimerFunc(20, simulation, 0);
};


#ifdef CHANGE_TIME_MS
void change_color_by_timer(int value) {
	// ����� ����� �� ������� ������ CHANGE_TIME_MS ��
	index = (index + 1) % max_index;
	glutPostRedisplay();
	// ��� �� ������� ����� ������� ��� ��� �����  ��
	glutTimerFunc(CHANGE_TIME_MS, change_color_by_timer, 0);
}
#endif

// ������� ��������� ������� ������
void keyboardFunc(unsigned char key, int x, int y)
{
	index = (index + 1) % max_index;
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
	
	#ifdef CHANGE_TIME_MS
	glutTimerFunc(20, change_color_by_timer, 0); // ����� ����� �� ������� ������ CHANGE_TIME_MS ��
	#endif

	// �������� ���� ��������� ��������� ��
	glutMainLoop();
};
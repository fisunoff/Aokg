#include <windows.h>

#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

// используем пространство имен стандартной библиотеки
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


// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, (float)w / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void)
{
	// отчищаем буфер цвета и буфер глубины
	glClearColor(0.2, 0.88, 0.11, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);

	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 7.5, 0, 0, 0, 0, 1, 0);

	// выводим объект - красный (1,0,0) чайник
	auto color_now = colors[index];
	glColor3f(color_now[0], color_now[1], color_now[2]);
	glutWireTeapot(1.0);

	// смена переднего и заднего буферов
	glutSwapBuffers();
};

// функция вызывается каждые 20 мс
void simulation(int value)
{
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, simulation, 0);
};


#ifdef CHANGE_TIME_MS
void change_color_by_timer(int value) {
	// смена цвета по таймеру каждые CHANGE_TIME_MS мс
	index = (index + 1) % max_index;
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через  мс
	glutTimerFunc(CHANGE_TIME_MS, change_color_by_timer, 0);
}
#endif

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y)
{
	index = (index + 1) % max_index;
	printf("Key code is %i\n Color changed\n", key);
};

void main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");

	// инициализация библиотеки GLUT
	glutInit(&argc, argv);
	// инициализация дисплея (формат вывода)
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	// СОЗДАНИЕ ОКНА:
	// 1. устанавливаем верхний левый угол окна
	glutInitWindowPosition(200, 200);
	// 2. устанавливаем размер окна
	glutInitWindowSize(800, 600);
	// 3. создаем окно
	glutCreateWindow("Laba_01");

	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// устанавливаем функцию, которая будет вызвана через 20 мс
	glutTimerFunc(20, simulation, 0);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(keyboardFunc);
	
	#ifdef CHANGE_TIME_MS
	glutTimerFunc(20, change_color_by_timer, 0); // смена цвета по таймеру каждые CHANGE_TIME_MS мс
	#endif

	// основной цикл обработки сообщений ОС
	glutMainLoop();
};
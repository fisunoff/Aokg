#include <windows.h>

#include <iostream>
#include <vector>

#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "GraphicObject.h"

// используем пространство имен стандартной библиотеки
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
vector<GraphicObject> graphicObjects;
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
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10, 15, 17.5, 0, 0, 0, 0, 1, 0);
	// выводим все графические объекты
	for (auto& go : graphicObjects) {
		go.draw();
	}
	// смена переднего и заднего буферов
	glutSwapBuffers();
};

void change_color() {
	// смена цвета по таймеру каждые CHANGE_TIME_MS мс
	index = (index + 1) % max_index; // двигаем индекс на следующий, зацикленно
	cout << "Changed color to " << colors[index][0] << " " << colors[index][1] << " " << colors[index][2] << endl;
}

// функция вызывается каждые 20 мс
void simulation(int value)
{
	// устанавливаем признак того, что окно нуждается в перерисовке
	glutPostRedisplay();
	// эта же функция будет вызвана еще раз через 20 мс
	glutTimerFunc(20, simulation, 0);
	timer += 20;
	if (timer >= CHANGE_TIME_MS) { // Если прошло CHANGE_TIME_MS, то меняем цвет и уменьшаем timer
		change_color();
		timer -= CHANGE_TIME_MS;
	}
};

// Функция обработки нажатия клавиш
void keyboardFunc(unsigned char key, int x, int y)
{
	change_color();
	printf("Key code is %i\n Color changed\n", key);
};

void main(int argc, char** argv)
{
	setlocale(LC_ALL, "ru");

	GraphicObject obj1;
	obj1.setPosition(glm::vec3(4, 0, 0));
	obj1.setAngle(180);
	obj1.setСolor(glm::vec3(1, 0, 0));
	graphicObjects.push_back(obj1);

	GraphicObject obj2;
	obj2.setPosition(glm::vec3(-4, 0, 0));
	obj2.setAngle(0);
	obj2.setСolor(glm::vec3(1, 1, 1));
	graphicObjects.push_back(obj2);

	GraphicObject obj3;
	obj3.setPosition(glm::vec3(0, 0, 4));
	obj3.setAngle(270);
	obj3.setСolor(glm::vec3(0, 1, 0));
	graphicObjects.push_back(obj3);

	GraphicObject obj4;
	obj4.setPosition(glm::vec3(0, 0, -4));
	obj4.setAngle(90);
	obj4.setСolor(glm::vec3(0, 0, 1));
	graphicObjects.push_back(obj4);

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
	glutCreateWindow("Laba_03");

	// УСТАНОВКА ФУНКЦИЙ ОБРАТНОГО ВЫЗОВА
	// устанавливаем функцию, которая будет вызываться для перерисовки окна
	glutDisplayFunc(display);
	// устанавливаем функцию, которая будет вызываться при изменении размеров окна
	glutReshapeFunc(reshape);
	// устанавливаем функцию, которая будет вызвана через 20 мс
	glutTimerFunc(20, simulation, 0);
	// устанавливаем функцию, которая будет вызываться при нажатии на клавишу
	glutKeyboardFunc(keyboardFunc);

	// основной цикл обработки сообщений ОС
	glutMainLoop();
};
#include "display.h"

// функция, вызываемая при изменении размеров окна
void reshape(int w, int h)
{
	// установить новую область просмотра, равную всей области окна
	glViewport(0, 0, GLsizei(w), GLsizei(h));
	// установить матрицу проекции с правильным аспектом
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(25.0, GLfloat(w) / h, 0.2, 70.0);
};

// функция вызывается при перерисовке окна
// в том числе и принудительно, по командам glutPostRedisplay
void display(void)
{
	glClearColor(0.00, 0.00, 0.00, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// включаем тест глубины
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	// устанавливаем камеру
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.apply();
	// устанавливаем источник света
	light.apply(GL_LIGHT0);
	planeGraphicObject.draw();
	player->draw();
	for (auto& row : mapObjects) {
		for (auto& elem : row)
			if (elem != nullptr) elem->draw();
	}

	// смена переднего и заднего буферов
	glutSwapBuffers();
};
#include "simulation.h"

float getFPS() {
	long long oldTicks = ticks.LowPart;
	QueryPerformanceCounter(&ticks);
	long long newTicks = ticks.LowPart - oldTicks;
	QueryPerformanceFrequency(&ticksPerSecond);
	float rez = ticksPerSecond.QuadPart / newTicks;
	return rez;
}

void simulation()
{
	int fps = getFPS();
	glutSetWindowTitle(to_string(fps).c_str());
	keyboard(fps);
	// сразу говорим, что можно рисовать заново
	glutPostRedisplay();

};
void keyboard(int fps)
{
	int keyLeft = GetAsyncKeyState(VK_LEFT);
	int keyRight = GetAsyncKeyState(VK_RIGHT);
	int keyUp = GetAsyncKeyState(VK_UP);
	int keyDown = GetAsyncKeyState(VK_DOWN);
	int keyPlus = GetAsyncKeyState(VK_ADD);
	int keySub = GetAsyncKeyState(VK_SUBTRACT);
	// для провекри класса камеры вызываем методы передвижения
	if (keyUp & 0x01)
	{
		camera.rotateUpDown(second_delta / fps);
	}
	if (keyDown & 0x01)
	{
		camera.rotateUpDown(-second_delta / fps);
	}
	if (keyRight & 0x01)
	{
		camera.rotateLeftRight(second_delta / fps);
	}
	if (keyLeft & 0x01)
	{
		camera.rotateLeftRight(-second_delta / fps);
	}
	if (keyPlus & 0x01)
	{
		camera.zoomInOut(zoom_second_delta / fps);
	}
	if (keySub & 0x01)
	{
		camera.zoomInOut(-zoom_second_delta / fps);
	}

};
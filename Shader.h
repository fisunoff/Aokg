#pragma once

#include <string>
#include <GL/glew.h>
#include <gl/GL.h>


// КЛАСС ДЛЯ РАБОТЫ С ШЕЙДЕРОМ
class Shader
{
public:
	// загрузка шейдера из внешних файлов
	bool load(std::string veftexShaderFilename, std::string fragmentShaderFilename);
	// выбор шейдера в качестве текущего
	void activate();
	// отключение шейдера
	static void deactivate();
private:
	// создание шейдерного объекта указанного типа
	// и загрузка исходного текста шейдера из указанного файла
	GLuint createShaderObject(GLenum shaderType, std::string filename);
private:
	// шейдерная программа (шейдер)
	GLuint program;
};

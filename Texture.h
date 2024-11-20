#pragma once
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/freeglut.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/hash.hpp>

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
using namespace std;
// ПЕРЕЧИСЛЕНИЕ ДЛЯ ОПРЕДЕЛЕНИЯ РЕЖИМА ФИЛЬТРАЦИИ
enum class TextureFilter {
	POINT, // ТОЧЕЧНАЯ
	BILINEAR, // БИЛИНЕЙНАЯ
	TRILINEAR, // ТРИЛИНЕЙНАЯ
	ANISOTROPIC // АНИЗТОРОПНАЯ
};
// КЛАСС ДЛЯ РАБОТЫ С ТЕКСТУРОЙ
class Texture
{
public:
	Texture();
	// загрузка текстуры из внешнего файла
	void load(std::string filename);

	// применение текстуры (привзяка к текстурному блоку и установка параметров)
	void apply(TextureFilter texFilter = TextureFilter::ANISOTROPIC);
	// отключение текстурирования для всех текстурных блоков
	static void disableAll();
private:
	// идентификатор (индекс) текстурного объекта
	GLuint texIndex;
};

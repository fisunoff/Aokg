#pragma once

#include "Data.h"

class Shader
{
public:
	// загрузка шейдера из внешних файлов
	bool load(std::string vertexShaderName, std::string fragmentShaderName);
	// выбор шейдера в качестве текущего
	void activate();
	// отключение шейдера
	static void deactivate();

	void setUniform(std::string name, int value);
	void setUniform(std::string name, float value);
	void setUniform(std::string name, glm::vec2);
	void setUniform(std::string name, glm::vec4);
	void setUniform(std::string name, glm::mat4);
private:
	// шейдерная программа (шейдер)
	GLuint program;
	static GLuint currentProgram;
	std::map<std::string, GLuint> uniforms;

	GLuint getUniformLocation(std::string name);
	GLuint createShaderObject(GLenum type, std::string sourcePath);
};

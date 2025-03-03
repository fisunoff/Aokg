#include "Shader.h"


bool Shader::load(std::string vertexShaderFileName, std::string fragmentShaderFilename){
	GLuint vertexShader = createShaderObject(GL_VERTEX_SHADER, vertexShaderFileName);
	if (!vertexShader)
	{
		std::ofstream crash_log("crash_" + std::to_string(time(nullptr)) + ".log");
		crash_log << "Compilation error: vertex shader sourceFile - " << vertexShaderFileName;
		crash_log.close();
		return false;
	}

	GLuint fragmentShader = createShaderObject(GL_FRAGMENT_SHADER, fragmentShaderFilename);
	if (!fragmentShader)
	{
		std::ofstream crash_log("crash_" + std::to_string(time(nullptr)) + ".log");
		crash_log << "Compilation error: fragment shader sourceFile - " << fragmentShaderFilename;
		crash_log.close();
		glDeleteShader(vertexShader);
		return false;
	}
	// Создаем шейдерную программу
	program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);	
	glLinkProgram(program);

	// Проверка на ошибки линковки
	GLint linkResult;
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (linkResult) {
		this->uniforms.insert({ "color1",glGetUniformLocation(this->program, "color1") });
		this->uniforms.insert({ "color2",glGetUniformLocation(this->program, "color2") });
		this->uniforms.insert({ "offset",glGetUniformLocation(this->program, "offset") });

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		return true;
	}

	char errorMsg[1024];
	std::string crashLogFilename = "crash_" + std::to_string(time(nullptr)) + ".log";
	glGetProgramInfoLog(this->program, 1024, nullptr, errorMsg);
	std::ofstream crash_log(crashLogFilename);
	crash_log << "Linking error: sourceFiles - " << fragmentShaderFilename << "," << vertexShaderFileName << "\nLOG:" << errorMsg;
	crash_log.close();
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(program);
}

GLuint Shader::createShaderObject(GLenum type, std::string sourcePath)
{
	std::ifstream shaderFile(sourcePath);
	if (!shaderFile)
		return 0;


	shaderFile.seekg(0, shaderFile.end);
	std::vector<char> buffer(shaderFile.tellg());
	shaderFile.seekg(0, shaderFile.beg);
	shaderFile.read(buffer.data(), buffer.size());

	GLuint shaderID = glCreateShader(type);

	GLchar const* pointerToBuffer = buffer.data();
	glShaderSource(shaderID, 1, &pointerToBuffer, nullptr);
	glCompileShader(shaderID);

	GLint compileResult;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
	if (compileResult) //GL_TRUE
		return shaderID;
	char errorMsg[1024];
	glGetShaderInfoLog(shaderID, 1024, nullptr, errorMsg);
	std::ofstream crash_log("crash_" + std::to_string(time(nullptr)) + ".log");
	crash_log << "Compilation error: sourceFile - " << sourcePath << " " << "\nLOG:" << errorMsg;
	crash_log.close();
	return 0;
}

GLuint Shader::currentProgram = 0;

void Shader::deactivate()
{
	Shader::currentProgram = 0;
	glUseProgram(0);
}

void Shader::activate()
{
	Shader::currentProgram = this->program;
	glUseProgram(this->program);
}

GLuint Shader::getUniformLocation(std::string name)
{
	std::map<std::string, GLuint>::iterator position = this->uniforms.find(name);
	if (position != this->uniforms.end())
		return this->uniforms.find(name)->second;
	else
		return 0;
}

void Shader::setUniform(std::string name, int value)
{
	glUniform1i(getUniformLocation(name), value);
}

void Shader::setUniform(std::string name, float value)
{
	glUniform1f(getUniformLocation(name), value);
}

void Shader::setUniform(std::string name, glm::vec2 value)
{
	glUniform2fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setUniform(std::string name, glm::vec4 value)
{
	glUniform4fv(getUniformLocation(name), 1, glm::value_ptr(value));
}

void Shader::setUniform(std::string name, glm::mat4 value)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}
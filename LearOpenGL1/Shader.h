#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Shader
{
public:
	unsigned int ID;
	Shader(const char* vName, const char* fName)
	{
		string vertexPath = SHADER_PATH + vName;
		string fragmentPath = SHADER_PATH + fName;

		std::string vertexSource;
		std::string fragmentSource;
		std::ifstream vertexStream;
		std::ifstream fragmentStream;

		vertexStream.exceptions(std::ifstream::failbit| std::ifstream::badbit);
		fragmentStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vertexStream.open(vertexPath);
			fragmentStream.open(fragmentPath);

			std::stringstream vStream, fStream;
			vStream << vertexStream.rdbuf();
			fStream << fragmentStream.rdbuf();

			vertexStream.close();
			fragmentStream.close();
			vertexSource = vStream.str();
			fragmentSource = fStream.str();
		}
		catch (const std::exception&)
		{
			std::cout << std::string(vertexPath) << std::endl;
			std::cout << "ERROR:SHADER:READ FILE FAILED,VERTEX NAME:" << vertexPath << ",FRAGMENT PATH:" << fragmentPath << std::endl;
		}
		const char* vShaderCode = vertexSource.c_str();
		const char* fShaderCode = fragmentSource.c_str();

		int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);
		check_shader_compile(GL_VERTEX_SHADER, "VERTEX");

		int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);
		check_shader_compile(GL_FRAGMENT_SHADER, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		glLinkProgram(ID);
		check_shader_compile(ID, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	void use() 
	{
		glUseProgram(ID);
	}
	void set_int(const std::string u_name,int value) 
	{
		int vlocation = glGetUniformLocation(ID,u_name.c_str());
		glUniform1i(vlocation, value);
	}
	void set_float(const std::string u_name, float value) 
	{
		glUniform1f(glGetUniformLocation(ID, u_name.c_str()), value);
	}
	void set_bool(const std::string u_name, bool value) 
	{
		glUniform1i(glGetUniformLocation(ID, u_name.c_str()), (int)value);
	}
	void set_mat4(string u_name,const float* value)
	{
		int vlocation = glGetUniformLocation(ID, u_name.c_str());
		glUniformMatrix4fv(vlocation, 1, GL_FALSE,value);
	}
	void set_vec4(string u_name,const glm::vec4 &value) 
	{
		int vlocation = glGetUniformLocation(ID, u_name.c_str());
		glUniform4fv(vlocation, 1, &value[0]);
	}
	void set_vec3(string u_name, const glm::vec3& value)
	{
		int vlocation = glGetUniformLocation(ID, u_name.c_str());
		glUniform3fv(vlocation, 1, &value[0]);
	}
	~Shader();

private:
	const string SHADER_PATH = "../Shaders/";
	///检测shader是否创建完成
	void check_shader_compile(unsigned int shader,std::string s_type) 
	{
		int success;
		char infoLog[1024];
		if (s_type == "PROGRAM") 
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) 
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR:SHADER:CREATE SHADER PROGRAM FAILED," << infoLog << std::endl;
			}
		}
		else 
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR:SHADER:CREATE SHADER FAILED," << infoLog << std::endl;
			}
		}
	}
};

Shader::~Shader()
{
	glDeleteProgram(ID);
}

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
	Shader(const char* vName, const char* fName,const char* geometryShaderName = NULL)
	{
		string vertexPath = SHADER_PATH + vName;
		string fragmentPath = SHADER_PATH + fName;

		string vStr = load_shader_source(vertexPath);
		string fStr = load_shader_source(fragmentPath);
		const GLchar* vShaderCode = vStr.c_str();
		const GLchar* fShaderCode = fStr.c_str();

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vShaderCode, NULL);
		glCompileShader(vertexShader);
		check_shader_compile(GL_VERTEX_SHADER, "VERTEX");

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShader);
		check_shader_compile(GL_FRAGMENT_SHADER, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertexShader);
		glAttachShader(ID, fragmentShader);
		unsigned int geometryShader;
		if (geometryShaderName != NULL)
		{
			string gPath = SHADER_PATH + geometryShaderName;
			string gStr = load_shader_source(gPath);
			const GLchar* gShaderCode = gStr.c_str();
			geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometryShader, 1, &gShaderCode, NULL);
			glCompileShader(geometryShader);
			glAttachShader(ID, geometryShader);
		}

		glLinkProgram(ID);
		check_shader_compile(ID, "PROGRAM");

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		if (geometryShaderName != NULL) 
		{
			glDeleteShader(geometryShader);
		}
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
	//将shader中的uniform块绑定到value绑定点
	void bind_uniform_block(string block_name,int value) 
	{
		unsigned int blockIndex = glGetUniformBlockIndex(ID, block_name.c_str());
		glUniformBlockBinding(ID, blockIndex, value);
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
	string load_shader_source(string path) 
	{
		std::ifstream fileStream;
		string result;

		fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			fileStream.open(path);

			std::stringstream sStream;
			sStream << fileStream.rdbuf();

			fileStream.close();
			result = sStream.str();
		}
		catch (const std::exception&)
		{
			std::cout << std::string(path) << std::endl;
			std::cout << "ERROR:SHADER:READ FILE FAILED,SHADER NAME:" << path << std::endl;
		}

		return result;
	}
};

Shader::~Shader()
{
	glDeleteProgram(ID);
}

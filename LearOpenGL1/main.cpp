

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<iostream>
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
#include "SkyBox.h"
#include "FrameBuffer.h"
#include "UniformBlock.h"

#include "GeometryStudy.h"
#include "InstanceStudy.h"
#include "PlanetStrip.h"


const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
float texture_mix;
float deltaTime;
Camera mainCamera(glm::vec3(0, 0, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0, -180.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 lightWorldPos(1.2f, 1.0f, 2.0f);

//每次窗口大小被调整的时候调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//检测输入
void process_input(GLFWwindow* window);
//鼠标位置回调
void curson_position_callback(GLFWwindow* window, double posx, double posy);
//鼠标滚轮回调
void mouse_scroll_callback(GLFWwindow* window, double offsetx, double offsety);
//创建VAO并绑定VBO EBO
unsigned int create_vao(float* vertices, int v_length, unsigned int* indices, int i_length);
//加载纹理
unsigned int load_texture(const char* path,int pos,int tex_type);
//加载天空盒
unsigned int load_cube_map(vector<string> faces);

//旧的渲染代码
void OLD_Render() 
{
	//glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer.FBO);
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_STENCIL_TEST);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//设置清空屏幕所用的颜色
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	////glUseProgram(shaderProgram);
	////glBindVertexArray(VAO);
	////glDrawArrays(GL_TRIANGLES, 0,3);
	////glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	///*glActiveTexture(0);
	//glBindTexture(GL_TEXTURE_2D, specularTexture);
	//glActiveTexture(1);
	//glBindTexture(GL_TEXTURE_2D, specularTexture);*/
	////渲染天空盒

	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
	//glStencilMask(0xFF);
	//shaderProgram.use();
	//shaderProgram.set_vec3("light.position", lightWorldPos);
	//glm::vec3 lightAmbient = lightColor * glm::vec3(0.3f);
	//glm::vec3 lightDiff = lightColor * glm::vec3(0.8f);
	//shaderProgram.set_vec3("light.ambient", lightAmbient);
	//shaderProgram.set_vec3("light.diffuse", lightDiff);
	//shaderProgram.set_vec3("light.specular", glm::vec3(1.0f));
	//shaderProgram.set_float("light.constant", 1.0f);
	//shaderProgram.set_float("light.linear", 0.09f);
	//shaderProgram.set_float("light.quadratic", 0.032f);
	//shaderProgram.set_float("material.shininess", 2.0f);
	////矩阵变换
	//glm::mat4 model = glm::mat4(1.0f);
	//shaderProgram.set_mat4("model", glm::value_ptr(model));
	//shaderProgram.set_mat4("view", glm::value_ptr(mainCamera.get_view_matrix()));
	//shaderProgram.set_mat4("projection", glm::value_ptr(mainCamera.get_projection_matrix()));

	//shaderProgram.set_vec3("viewWorldPos", mainCamera.position);
	//mesh.Draw(shaderProgram);

	//glStencilMask(0x00);
	//model = glm::translate(model, glm::vec3(1.0f, -1.0f, 0.0f));
	//model = glm::scale(model, glm::vec3(0.1f));
	//shaderProgram.set_mat4("model", glm::value_ptr(model));
	//robot.Draw(shaderProgram);

	//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	//glStencilMask(0x00);
	//glDisable(GL_DEPTH_TEST);
	//lightProgram.use();
	//glm::mat4 model1 = glm::mat4(1.0f);
	//model1 = glm::scale(model1, glm::vec3(1.01f));
	//lightProgram.set_mat4("model", glm::value_ptr(model1));
	//lightProgram.set_mat4("view", glm::value_ptr(mainCamera.get_view_matrix()));
	//lightProgram.set_mat4("projection", glm::value_ptr(mainCamera.get_projection_matrix()));
	//lightProgram.set_vec3("lightColor", lightColor);
	//mesh.Draw(lightProgram);
	//glStencilMask(0xFF);
	//glEnable(GL_DEPTH_TEST);
	////shaderProgram.set_float("mixValue", texture_mix);
	///*glm::mat4 model;
	//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	//shaderProgram.set_mat4("model", glm::value_ptr(model));*/
	///*glBindVertexArray(VAO1);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);*/
	////glBindVertexArray(VAO2);
	////glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	//glDepthFunc(GL_LEQUAL);
	//skyboxProgram.use();
	////glm::mat4 modelsky = glm::mat4(1.0f);
	////modelsky = glm::scale(modelsky, glm::vec3(10));
	////skyboxProgram.set_mat4("model", glm::value_ptr(modelsky));
	//skyboxProgram.set_mat4("view", glm::value_ptr(glm::mat4(glm::mat3(mainCamera.get_view_matrix()))));
	//skyboxProgram.set_mat4("projection", glm::value_ptr(mainCamera.get_projection_matrix()));
	//skyBox.Draw(skyboxProgram);
	////渲染灯光物体
	////lightProgram.use();
	///*glm::mat4 lightModel;
	//lightModel = glm::translate(lightModel, lightWorldPos);
	//lightModel = glm::scale(lightModel, glm::vec3(0.2f));
	//lightProgram.set_mat4("model", glm::value_ptr(lightModel));
	//lightProgram.set_mat4("view", glm::value_ptr(mainCamera.get_view_matrix()));
	//lightProgram.set_mat4("projection", glm::value_ptr(mainCamera.get_projection_matrix()));
	//lightProgram.set_vec3("lightColor", lightColor);
	//mesh.Draw(lightProgram);*/

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//////回到默认帧缓冲
	//////渲染quad的mesh 将上面帧缓冲生产的图像 在这个mesh中渲染
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_STENCIL_TEST);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	////我用了 模板和深度的渲染缓冲 这里一定要清除掉 或者直接关掉模板和深度测试
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//quadShader.use();
	//glBindVertexArray(renderMesh.VAO);
	//glBindTexture(GL_TEXTURE_2D, frameBuffer.Render_Texture);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗口
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) 
	{ 
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, curson_position_callback);
	glfwSetScrollCallback(window, mouse_scroll_callback);
	//隐藏鼠标
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//初始化GLAD 管理opengl函数指针
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//创建shader程序(着色器)
	//vertex shader
	//const char *vertexShaderSource = "#version 330 core\n"
	//	"layout (location = 0) in vec3 aPos;\n"
	//	"void main()\n"
	//	"{\n"
	//		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	//	"}\n";
	//int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vertexShader, 1,&vertexShaderSource, NULL);
	//glCompileShader(vertexShader);
	//int success;
	//char infoLog[512];
	//glGetShaderiv(GL_VERTEX_SHADER, GL_COMPILE_STATUS,&success);
	//if (!success) 
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR:SHADER:VERTEXT:COMPILE:FAILED" << infoLog << std::endl;
	//}

	////fragment shader
	//const char *fragmentShaderSource = "#version 330 core\n"
	//	"out vec4 FragColor;\n"
	//	"void main()\n"
	//	"{\n"
	//		"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	//	"}\n";
	//int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);
	//glGetShaderiv(GL_FRAGMENT_SHADER, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
	//	std::cout << "ERROR:SHADER:FRAGMENT:COMPILE_FAILED:" << infoLog << std::endl;
	//}

	////创建着色器对象  Shader Program Object
	//unsigned int shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	//glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	//if (!success) 
	//{
	//	glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	//	std::cout << "ERROR:SHADER_PROGRAM:LINK_FAILED:" << infoLog << std::endl;
	//}

	//glDeleteShader(vertexShader);
	//glDeleteShader(fragmentShader);
	//openg函数

	//创建并绑定VBO 显存上的顶点缓存对象 创建VAO
	float vertices[] =
	{	//顶点               法线                 uv
	    -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
							 
		-0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
							 
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
							 
		 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
							 
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
							 
		-0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};
	unsigned int indices_old[] =
	{
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
		16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
	};
	//unsigned int VBO,VAO,EBO;
	//glGenVertexArrays(1, &VAO);//创建vao
	//glGenBuffers(1,&VBO);//创建vbo
	//glGenBuffers(1, &EBO);//创建EBO

	//glBindVertexArray(VAO);//绑定vao

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定vbo
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	////设置顶点属性指针
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定EBO
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//设定EBO数据

	////坑 需要注意的是，当VAO处于活动状态时，不能解绑EBO， 因为绑定的元素缓冲区对象存储在VAO中
	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//解绑EBO 
	//glBindBuffer(GL_ARRAY_BUFFER, 0);//解绑vbo
	//glBindVertexArray(0);//解绑vao
	
	vector<Vertex> meshVertices =
	{
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f),
		Vertex(0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  1.0f,  0.0f),
		Vertex(0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  1.0f,  1.0f),
		Vertex(0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  1.0f,  1.0f),
		Vertex(-0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.0f, 1.0f),
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.0f, 0.0f),

		Vertex(-0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f),
		Vertex(0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  1.0f,  0.0f),
		Vertex(0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  1.0f,  1.0f),
		Vertex(0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  1.0f,  1.0f),
		Vertex(-0.5f,  0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.0f, 1.0f),
		Vertex(-0.5f, -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.0f, 0.0f),

		Vertex(-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f),
		Vertex(-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f),
		Vertex(-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f),
		Vertex(-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f),
		Vertex(-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f),
		Vertex(-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f),

		Vertex(0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f),
		Vertex(0.5f,  0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 1.0f),
		Vertex(0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f),
		Vertex(0.5f, -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 1.0f),
		Vertex(0.5f, -0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  0.0f, 0.0f),
		Vertex(0.5f,  0.5f,  0.5f, 1.0f,  0.0f,  0.0f,  1.0f, 0.0f),

		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f),
		Vertex(0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  1.0f,  1.0f),
		Vertex(0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  1.0f,  0.0f),
		Vertex(0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  1.0f,  0.0f),
		Vertex(-0.5f, -0.5f,  0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 0.0f),
		Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -1.0f,  0.0f,  0.0f, 1.0f),

		Vertex(-0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f),
		Vertex(0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  1.0f),
		Vertex(0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  0.0f),
		Vertex(0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  1.0f,  0.0f),
		Vertex(-0.5f,  0.5f,  0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 0.0f),
		Vertex(-0.5f,  0.5f, -0.5f, 0.0f,  1.0f,  0.0f,  0.0f, 1.0f)
	};
	vector<unsigned int> indices =
	{
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
		16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35
	};
	
	//帧缓冲mesh顶点
	//float quadVertices[] = {
	//	// positions   // texCoords
	//	-1.0f,  1.0f,  0.0f, 1.0f,
	//	-1.0f, -1.0f,  0.0f, 0.0f,
	//	 1.0f, -1.0f,  1.0f, 0.0f,

	//	-1.0f,  1.0f,  0.0f, 1.0f,
	//	 1.0f, -1.0f,  1.0f, 0.0f,
	//	 1.0f,  1.0f,  1.0f, 1.0f
	//};
	//unsigned int VAO1 = create_vao(vertices,sizeof(vertices) ,indices,sizeof(indices));
#pragma region 天空盒
	/*
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
	vector<string> cubeMaps = {
		"../Textures/skybox/right.jpg",
		"../Textures/skybox/left.jpg",
		"../Textures/skybox/top.jpg",
		"../Textures/skybox/bottom.jpg",
		"../Textures/skybox/front.jpg",
		"../Textures/skybox/back.jpg"
	};
	unsigned int cube_map = load_cube_map(cubeMaps);

	unsigned int skyVAO, skyVBO;
	glGenVertexArrays(1, &skyVAO);
	glGenBuffers(1, &skyVBO);

	glBindVertexArray(skyVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(skyboxVertices),skyboxVertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	*/
#pragma endregion 天空盒

	//Mesh mesh(meshVertices,indices, {
	//	Texture("../Textures/container2.png","texture_diffuse"),
	//	Texture("../Textures/container2_specular.png","texture_specular")
	//});
	//Model robot("../Models/Robot/nanosuit.obj");
	//Mesh renderMesh(
	//{
	//	Vertex(-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
	//	Vertex(-1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
	//	Vertex( 1.0f,-1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
	//	Vertex( 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
	//},{0,1,2,2,3,0});
	//FrameBuffer frameBuffer(SCR_WIDTH, SCR_HEIGHT);

	//Shader shaderProgram("vert.vert", "frag.frag");
	//Shader lightProgram("lightVert.vert", "lightFrag.frag");
	//Shader quadShader("frameBuff.vert", "frameBuff.frag");
	//quadShader.use();
	//quadShader.set_int("screenTexture", 0);

	//UniformBlock uniformBlock(2 * sizeof(glm::mat4),0);
	//shaderProgram.bind_uniform_block("Matices", 0);
	////当相机发生的transform发生改变的时候 回调设置uniform块中的矩阵
	//mainCamera.on_transform_changed = [&uniformBlock]()
	//{
	//	uniformBlock.SetUniformData(0, sizeof(glm::mat4), glm::value_ptr(mainCamera.get_projection_matrix()));
	//	uniformBlock.SetUniformData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(mainCamera.get_view_matrix()));
	//};

	//shaderProgram.set_vec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
	//shaderProgram.set_vec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	//shaderProgram.set_int("material.mainTexture", 0);
	//shaderProgram.set_vec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	//shaderProgram.set_int("material.specularTexture", 1);
#pragma region 帧缓冲代码
	/*
	//帧缓冲代码
	unsigned int FBO;
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	//给帧缓冲附加纹理对象
	unsigned int fbo_texture;
	glGenTextures(1, &fbo_texture);
	glBindTexture(GL_TEXTURE_2D, fbo_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo_texture, 0);
	//添加渲染缓冲对象 只能写入 不能读取 用来储存深度和模板信息 速度相对于纹理 更快
	unsigned int rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	//恢复默认的帧缓冲
	//检测帧缓冲是否创建完毕
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
	{
		cout << "ERROR:FRAMEBUFFER:FRAME NOT COMPLETE" << endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//创建帧缓冲mesh
	unsigned int quadVAO;
	unsigned int quadVBO;
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	
	glBindVertexArray(quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices),quadVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);

	//给mesh创建shader
	Shader quadShader("frameBuff.vert", "frameBuff.frag");
	quadShader.use();
	quadShader.set_int("screenTexture", 0);
	*/
#pragma endregion 帧缓冲代码


	//光源模型
	//unsigned int lightVAO = create_vao(vertices, sizeof(vertices), indices_old, sizeof(indices_old));

	SkyBox skyBox({
		"../Textures/skybox/right.jpg",
		"../Textures/skybox/left.jpg",
		"../Textures/skybox/top.jpg",
		"../Textures/skybox/bottom.jpg",
		"../Textures/skybox/front.jpg",
		"../Textures/skybox/back.jpg"
		});
	Shader skyboxProgram("skyboxvert.vert", "skyboxfrag.frag");
	/*UniformBlock uniformBlock(2 * sizeof(glm::mat4), 0);
	GeometryStudy gStudy(&mainCamera,&uniformBlock);*/
	InstanceStudy iStudy;

	//绘制前的设置
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式
	//渲染画面
	float lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		process_input(window);//每帧开始 检测输入

		glClearColor(0.0f,0.0f,0.0f,1.0f);//设置清空屏幕所用的颜色
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		//glEnable(GL_PROGRAM_POINT_SIZE);

		////渲染箱子
		//shaderProgram.use();
		//shaderProgram.set_vec3("light.position", lightWorldPos);
		//glm::vec3 lightAmbient = lightColor * glm::vec3(0.3f);
		//glm::vec3 lightDiff = lightColor * glm::vec3(0.8f);
		//shaderProgram.set_vec3("light.ambient", lightAmbient);
		//shaderProgram.set_vec3("light.diffuse", lightDiff);
		//shaderProgram.set_vec3("light.specular", glm::vec3(1.0f));
		//shaderProgram.set_float("light.constant", 1.0f);
		//shaderProgram.set_float("light.linear", 0.09f);
		//shaderProgram.set_float("light.quadratic", 0.032f);
		//shaderProgram.set_float("material.shininess", 2.0f);
		////矩阵变换
		//glm::mat4 model = glm::mat4(1.0f);
		//shaderProgram.set_mat4("model", glm::value_ptr(model));

		//shaderProgram.set_vec3("viewWorldPos", mainCamera.position);
		//mesh.Draw(shaderProgram);
		iStudy.Render();

		//最后渲染天空盒
		glDepthFunc(GL_LEQUAL);
		skyboxProgram.use();
		skyboxProgram.set_mat4("view", glm::value_ptr(glm::mat4(glm::mat3(mainCamera.get_view_matrix()))));
		skyboxProgram.set_mat4("projection", glm::value_ptr(mainCamera.get_projection_matrix()));
		skyBox.Draw(skyboxProgram);

		glfwSwapBuffers(window);//交换颜色缓冲
		glfwPollEvents();//检测鼠标键盘输入
	}

	//资源清理
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);*/
	//glDeleteProgram(shaderProgram);

	glfwTerminate();//释放资源
	return 0;
}

unsigned int create_vao(float* vertices,int v_length, unsigned int* indices,int i_length)
{
	unsigned int VAO,VBO,EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1,&VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, v_length,vertices, GL_STATIC_DRAW);
	//传入顶点
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//传入法线
	glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//传入uv坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_length, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return VAO;
}

unsigned int load_texture(const char* path,int pos,int tex_type)
{
	unsigned int texture; 
	glGenTextures(1, &texture);
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 

	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &width, &height, &nrChannel, 0);
	if (!data)
	{
		cout << "load image error!" << endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, tex_type, width, height, 0, tex_type, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	return texture;
}

unsigned int load_cube_map(vector<string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
	int width, height, nrChannel;
	stbi_set_flip_vertically_on_load(false);
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannel, 0);
		if (data) 
		{
			GLenum format;
			if (nrChannel == 1)
			{
				format = GL_RED;
			}
			else if (nrChannel == 3)
			{
				format = GL_RGB;
			}
			else if (nrChannel == 4)
			{
				format = GL_RGBA;
			}
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,format, width, height, 0, format, GL_UNSIGNED_BYTE,data);
			stbi_image_free(data);
		}
		else 
		{
			cout << "load image error!" << faces[i] << endl;
			stbi_image_free(data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	return textureID;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
}

void process_input(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		mainCamera.process_keyboard(FORWARD, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		mainCamera.process_keyboard(BACK, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		mainCamera.process_keyboard(LEFT, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		mainCamera.process_keyboard(RIGHT, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		mainCamera.process_keyboard(UP, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		mainCamera.process_keyboard(DOWN, deltaTime);
	}
}

float lastMouseX = 0;
float lastMouseY = 0;
bool firstMouse = true;
void curson_position_callback(GLFWwindow* window, double posx, double posy)
{
	if (firstMouse) 
	{
		lastMouseX = posx;
		lastMouseY = posy;
		firstMouse = false;
	}
	float deltax = posx - lastMouseX;
	float deltay = lastMouseY - posy;
	lastMouseX = posx;
	lastMouseY = posy;

	mainCamera.process_mouse_movement(deltax, deltay);
}

void mouse_scroll_callback(GLFWwindow* window, double offsetx, double offsety)
{
	mainCamera.process_mouse_scroll(offsety);
}

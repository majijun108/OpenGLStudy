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

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
float texture_mix;
float deltaTime;
Camera mainCamera(glm::vec3(0, 0, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0, -180.0f);
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 lightWorldPos(1.2f, 1.0f, 2.0f);

//ÿ�δ��ڴ�С��������ʱ�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//�������
void process_input(GLFWwindow* window);
//���λ�ûص�
void curson_position_callback(GLFWwindow* window, double posx, double posy);
//�����ֻص�
void mouse_scroll_callback(GLFWwindow* window, double offsetx, double offsety);
//����VAO����VBO EBO
unsigned int create_vao(float* vertices, int v_length, unsigned int* indices, int i_length);
//��������
unsigned int load_texture(const char* path,int pos,int tex_type);

int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//��������
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

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//��ʼ��GLAD ����opengl����ָ��
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//����shader����(��ɫ��)
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

	////������ɫ������  Shader Program Object
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
	//openg����

	//��������VBO �Դ��ϵĶ��㻺����� ����VAO
	float vertices[] =
	{	//����               ����                 uv
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
	//glGenVertexArrays(1, &VAO);//����vao
	//glGenBuffers(1,&VBO);//����vbo
	//glGenBuffers(1, &EBO);//����EBO

	//glBindVertexArray(VAO);//��vao

	//glBindBuffer(GL_ARRAY_BUFFER, VBO);//��vbo
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	////���ö�������ָ��
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//��EBO
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//�趨EBO����

	////�� ��Ҫע����ǣ���VAO���ڻ״̬ʱ�����ܽ��EBO�� ��Ϊ�󶨵�Ԫ�ػ���������洢��VAO��
	////glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//���EBO 
	//glBindBuffer(GL_ARRAY_BUFFER, 0);//���vbo
	//glBindVertexArray(0);//���vao
	
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
	//unsigned int VAO1 = create_vao(vertices,sizeof(vertices) ,indices,sizeof(indices));
	unsigned int texture = load_texture("../Textures/container2.png",0,GL_RGBA);
	unsigned int specularTexture = load_texture("../Textures/container2_specular.png", 1, GL_RGBA);
	vector<Texture> textures = {
		Texture(texture,"texture_diffuse"),
		Texture(specularTexture,"texture_specular")
	};

	Mesh mesh(meshVertices,indices,textures);

	Shader shaderProgram("vert.vert", "frag.frag");

	//shaderProgram.set_vec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
	//shaderProgram.set_vec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
	//shaderProgram.set_int("material.mainTexture", 0);
	//shaderProgram.set_vec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	//shaderProgram.set_int("material.specularTexture", 1);

	//��Դģ��
	//unsigned int lightVAO = create_vao(vertices, sizeof(vertices), indices_old, sizeof(indices_old));
	Shader lightProgram("lightVert.vert", "lightFrag.frag");


	//����ǰ������
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//�߿�ģʽ
	//��Ⱦ����
	float lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		process_input(window);//ÿ֡��ʼ �������
		glEnable(GL_DEPTH_TEST);
		glClearColor(0.0f,0.0f,0.0f,1.0f);//���������Ļ���õ���ɫ
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		//glUseProgram(shaderProgram);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0,3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		/*glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, specularTexture);
		glActiveTexture(1);
		glBindTexture(GL_TEXTURE_2D, specularTexture);*/
		shaderProgram.use();
		shaderProgram.set_vec3("light.position", lightWorldPos);
		glm::vec3 lightAmbient = lightColor * glm::vec3(0.3f);
		glm::vec3 lightDiff = lightColor * glm::vec3(0.8f);
		shaderProgram.set_vec3("light.ambient", lightAmbient);
		shaderProgram.set_vec3("light.diffuse", lightDiff);
		shaderProgram.set_vec3("light.specular", glm::vec3(1.0f));
		shaderProgram.set_float("light.constant", 1.0f);
		shaderProgram.set_float("light.linear", 0.09f);
		shaderProgram.set_float("light.quadratic", 0.032f);
		shaderProgram.set_float("material.shininess", 32.0f);
		//����任
		glm::mat4 model = glm::mat4(1.0f);
		shaderProgram.set_mat4("model", glm::value_ptr(model));
		shaderProgram.set_mat4("view", glm::value_ptr(mainCamera.get_view_matrix()));
		shaderProgram.set_mat4("projection", glm::value_ptr(mainCamera.get_projection_matrix()));

		shaderProgram.set_vec3("viewWorldPos", mainCamera.position);
		mesh.Draw(shaderProgram);
		//shaderProgram.set_float("mixValue", texture_mix);
		/*glm::mat4 model;
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		shaderProgram.set_mat4("model", glm::value_ptr(model));*/
		/*glBindVertexArray(VAO1);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);*/
		//glBindVertexArray(VAO2);
		//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		//��Ⱦ�ƹ�����
		lightProgram.use();
		glm::mat4 lightModel;
		lightModel = glm::translate(lightModel, lightWorldPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
		lightProgram.set_mat4("model", glm::value_ptr(lightModel));
		lightProgram.set_mat4("view", glm::value_ptr(mainCamera.get_view_matrix()));
		lightProgram.set_mat4("projection", glm::value_ptr(mainCamera.get_projection_matrix()));
		lightProgram.set_vec3("lightColor", lightColor);
		mesh.Draw(lightProgram);

		glfwPollEvents();//�������������
		glfwSwapBuffers(window);//������ɫ����
	}

	//��Դ����
	/*glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);*/
	//glDeleteProgram(shaderProgram);

	glfwTerminate();//�ͷ���Դ
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
	//���붥��
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//���뷨��
	glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	//����uv����
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
	glActiveTexture(GL_TEXTURE0);
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
#pragma once
//������ɫ��ѧϰ
class GeometryStudy
{
public:
	
	GeometryStudy(UniformBlock* uniformBlock);
	~GeometryStudy();

	void Render() 
	{
		shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_POINTS, 0, 4);

		shaderProgram.use();
		shaderProgram.set_vec3("light.position", glm::vec3(1.2f, 1.0f, 2.0f));
		glm::vec3 lightAmbient = glm::vec3(1.0f, 1.0f, 1.0f) * glm::vec3(0.3f);
		glm::vec3 lightDiff = glm::vec3(1.0f, 1.0f, 1.0f) * glm::vec3(0.8f);
		shaderProgram.set_vec3("light.ambient", lightAmbient);
		shaderProgram.set_vec3("light.diffuse", lightDiff);
		shaderProgram.set_vec3("light.specular", glm::vec3(1.0f));
		shaderProgram.set_float("light.constant", 1.0f);
		shaderProgram.set_float("light.linear", 0.09f);
		shaderProgram.set_float("light.quadratic", 0.032f);
		shaderProgram.set_float("material.shininess", 2.0f);
		//����任
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.1f));
		shaderProgram.set_mat4("model", glm::value_ptr(model));
		//ʱ�����
		shaderProgram.set_float("time", glfwGetTime());

		shaderProgram.set_vec3("viewWorldPos", Camera::main->position);
		robot.Draw(shaderProgram);
	}

private:
	float points[20] =
	{
		-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // ����
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f,// ����
		 0.5f, -0.5f, 1.0f, 1.0f, 0.0f,// ����
		-0.5f, -0.5f, 1.0f, 0.0f, 1.0f  // ����
	};
	unsigned int VAO;  
	unsigned int VBO;
	Shader shader;
	Model robot;
	Shader shaderProgram;
	UniformBlock* uniformBlock;

	void InitModel()
	{
		shaderProgram.bind_uniform_block("Matices", 0);
		//�����������transform�����ı��ʱ�� �ص�����uniform���еľ���
		Camera::main->on_transform_changed.push_back([this]()
		{
			uniformBlock->SetUniformData(0, sizeof(glm::mat4), glm::value_ptr(Camera::main->get_projection_matrix()));
			uniformBlock->SetUniformData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(Camera::main->get_view_matrix()));
		});
	}
};

GeometryStudy::GeometryStudy(UniformBlock* uniformBlock):shader("geometryVert.vert","geometryFrag.frag","geometryGS.gs")
,robot("../Models/Robot/nanosuit.obj"), shaderProgram("vert.vert", "frag.frag","explodeGeo.gs")
{
	this->uniformBlock = uniformBlock;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	InitModel();
}

GeometryStudy::~GeometryStudy()
{
}

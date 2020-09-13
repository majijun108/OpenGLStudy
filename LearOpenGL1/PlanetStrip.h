#pragma once

class PlanetStrip
{
public:
	PlanetStrip(UniformBlock*uniform);
	~PlanetStrip();
	void Render();
private:
	Model* planet;
	Model* rock;
	Shader* shader;
	Shader* rockShader;
	UniformBlock* uniformBlock;

	unsigned int instanceVBO;
	unsigned int amount = 10000;//渲染的小行星的数量
	glm::mat4* modelMatrices;

	//生产模型举证
	void GenModelMatrices() 
	{
		modelMatrices = new glm::mat4[amount];
		float radius = 10.0;
		float offset = 2.5f;

		srand(glfwGetTime());//初始化随机种子
		for (unsigned int i = 0; i < amount; i++)
		{
			glm::mat4 model;
			float angle = (float)i / (float)amount * 360.0f;
			float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
			float x = sin(angle) * radius + displacement;
			displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
			float y = displacement * 0.4f; // 让行星带的高度比x和z的宽度要小
			displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
			float z = cos(angle) * radius + displacement;
			model = glm::translate(model, glm::vec3(x, y, z));

			// 2. 缩放：在 0.05 和 0.25f 之间缩放
			float scale = (rand() % 20) / 100.0f + 0.05;
			model = glm::scale(model, glm::vec3(scale));

			// 3. 旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
			float rotAngle = (rand() % 360);
			model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
			modelMatrices[i] = model;
		}
	}

	//生成实例化数组
	void GenInstanceVBO() 
	{
		glGenBuffers(1, &instanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SetInstanceVBO() 
	{
		glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
		for (unsigned int i = 0; i < rock->meshes.size(); i++)
		{
			unsigned int vao = rock->meshes[i].VAO;
			glBindVertexArray(vao);

			GLsizei vec4size = sizeof(glm::vec4);
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4size, (void*)0);

			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4size, (void*)vec4size);

			glEnableVertexAttribArray(5);
			glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4size, (void*)(2*vec4size));

			glEnableVertexAttribArray(6);
			glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4size, (void*)(3* vec4size));

			glVertexAttribDivisor(3, 1);
			glVertexAttribDivisor(4, 1);
			glVertexAttribDivisor(5, 1);
			glVertexAttribDivisor(6, 1);

			glBindVertexArray(0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};

PlanetStrip::PlanetStrip(UniformBlock* uniform)
{
	this->uniformBlock = uniform;
	planet = new Model("../Models/Planet/planet.obj");
	rock = new Model("../Models/Rock/rock.obj");
	shader = new Shader("planet.vs", "planet.fs");
	rockShader = new Shader("rock.vs", "planet.fs");

	shader->bind_uniform_block("Matices", 0);
	Camera::main->on_transform_changed.push_back([this]()
	{
		uniformBlock->SetUniformData(0, sizeof(glm::mat4), glm::value_ptr(Camera::main->get_projection_matrix()));
		uniformBlock->SetUniformData(sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(Camera::main->get_view_matrix()));
	});

	GenModelMatrices();
	GenInstanceVBO();
	SetInstanceVBO();
}

inline void PlanetStrip::Render()
{
	shader->use();
	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
	shader->set_mat4("model", glm::value_ptr(model));
	planet->Draw(*shader);
	
	rockShader->use();
	//rock->Draw(*rockShader);
	rock->DrawInstance(rockShader,amount);
}

PlanetStrip::~PlanetStrip()
{
	delete planet;
	delete rock;
	delete shader;
	delete modelMatrices;
}

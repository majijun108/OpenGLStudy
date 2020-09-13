#pragma once
//实例化学习

class InstanceStudy
{
public:
	InstanceStudy();
	~InstanceStudy();
	void Render();
private:
	float vertices[30] = {
			// 位置          // 颜色
		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		-0.05f, -0.05f,  0.0f, 0.0f, 1.0f,

		-0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
		 0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
		 0.05f,  0.05f,  0.0f, 1.0f, 1.0f
	};

	unsigned int VAO;
	unsigned int VBO;
	unsigned int InstanceVBO;
	glm::vec2 translations[100];
	Shader shader;

	void InitInstanceOffset() 
	{
		int index = 0;
		float offset = 0.1f;
		for (int y = -10; y < 10; y += 2)
		{
			for (int x = -10; x < 10; x += 2)
			{
				glm::vec2 translation;
				translation.x = (float)x / 10.0f + offset;
				translation.y = (float)y / 10.0f + offset;
				translations[index++] = translation;
			}
		}
	}
	void Setup() 
	{
		InitInstanceOffset();
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//实例化数组
		glGenBuffers(1, &InstanceVBO);
		glBindBuffer(GL_ARRAY_BUFFER, InstanceVBO);
		glBufferData(GL_ARRAY_BUFFER, 100 * sizeof(glm::vec2),&translations[0], GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribDivisor(2, 1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}
};

InstanceStudy::InstanceStudy():shader("instanceVert.vs", "instanceFrag.fs")
{
	Setup();
}

void InstanceStudy::Render() 
{
	shader.use();
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100);
}

InstanceStudy::~InstanceStudy()
{
}
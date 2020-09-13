#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"
#include "Texture.h"

#include <string>
#include <vector>


struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	Vertex() {};
	Vertex(glm::vec3 pos,glm::vec3 nor,glm::vec2 uv) 
	{
		this->Position = pos;
		this->Normal = nor;
		this->TexCoords = uv;
	}
	Vertex(float p_x,float p_y,float p_z,float n_x,float n_y,float n_z,float u_x,float u_y)
	{
		this->Position = glm::vec3(p_x, p_y, p_z);
		this->Normal = glm::vec3(n_x, n_y, n_z);
		this->TexCoords = glm::vec2(u_x,u_y);
	}
};

//struct Texture
//{
//	unsigned int id;
//	string type;
//	string path;
//	Texture() {}
//	Texture(unsigned int id,string type) 
//	{
//		this->id = id;
//		this->type = type;
//	}
//};

class Mesh {
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		SetupMesh();
	}

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices)
	{
		this->vertices = vertices;
		this->indices = indices;
		SetupMesh();
	}

	void Draw(Shader &shader) 
	{
		BindTextures(shader);

		glBindVertexArray(VAO);
		//渲染点的时候 需要GL_POINTS
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void DrawInstance(Shader* shader,unsigned int &count) 
	{
		BindTextures(*shader);

		glBindVertexArray(VAO);
		//渲染点的时候 需要GL_POINTS
		glDrawElementsInstanced(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0,count);
		glBindVertexArray(0);
	}

private:
	unsigned int VBO, EBO;
	void SetupMesh() 
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
		//顶点位置
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
		glEnableVertexAttribArray(0);
		//法线位置
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
		glEnableVertexAttribArray(1);
		//纹理坐标
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	void BindTextures(Shader& shader)
	{
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			string number;
			string name = textures[i].type;
			if (name == "texture_diffuse")
			{
				number = std::to_string(diffuseNr++);
			}
			else if (name == "texture_specular")
			{
				number = std::to_string(specularNr++);
			}

			shader.set_int("material." + name + number, i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		glActiveTexture(GL_TEXTURE0);
	}
};
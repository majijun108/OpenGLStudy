#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Shader.h"
#include "Mesh.h"

#include<vector>
#include<string>

class Model 
{
	public:
		Model(string path) 
		{
			load_model(path);
		}
		void Draw(Shader &shader) 
		{
			for (unsigned int i = 0; i < meshes.size(); i++)
			{
				meshes[i].Draw(shader);
			}
		}

	private:
		vector<Mesh> meshes;
		string directory;

		void load_model(string path) 
		{
			Assimp::Importer importer;
			const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
			{
				cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
				return;
			}
			directory = path.substr(0, path.find_last_of('/'));

			process_node(scene->mRootNode, scene);
		}

		void process_node(aiNode* node, const aiScene* scene) 
		{
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(process_mesh(mesh, scene));
			}
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				process_node(node->mChildren[i],scene);
			}
		}

		Mesh process_mesh(aiMesh *mesh,const aiScene * scene) 
		{
			vector<Vertex> vertices;
			vector<unsigned int> indices;
			vector<Texture> textures;
			//处理顶点
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) 
			{
				Vertex vertex;

				glm::vec3 pos;
				pos.x = mesh->mVertices[i].x;
				pos.y = mesh->mVertices[i].y;
				pos.z = mesh->mVertices[i].z;
				vertex.Position = pos;

				glm::vec3 normal;
				normal.x = mesh->mNormals[i].x;
				normal.y = mesh->mNormals[i].y;
				normal.z = mesh->mNormals[i].z;
				vertex.Normal = normal;

				if (mesh->mTextureCoords[0]) 
				{
					glm::vec2 texcoord;
					texcoord.x = mesh->mTextureCoords[0][i].x;
					texcoord.y = mesh->mTextureCoords[0][i].y;
					vertex.TexCoords = texcoord;
				}
				else
				{
					vertex.TexCoords = glm::vec2(0.0f);
				}
				vertices.push_back(vertex);
			}
			//处理索引
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
				{
					indices.push_back(face.mIndices[j]);
				}
			}
			//处理贴图
			if (mesh->mMaterialIndex >= 0) 
			{
				aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

				vector<Texture> diffs = load_material_texture(material, aiTextureType_DIFFUSE, "texture_diffuse");
				textures.insert(textures.end(), diffs.begin(), diffs.end());

				vector<Texture> specs = load_material_texture(material, aiTextureType_SPECULAR, "texture_specular");
				textures.insert(textures.end(), specs.begin(), specs.end());
			}

			Mesh result_mesh(vertices, indices, textures);
			return result_mesh;
		}

		vector<Texture> load_material_texture(aiMaterial* material, aiTextureType type, string typeName) 
		{
			vector<Texture> textures;
			for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
			{
				aiString path;
				material->GetTexture(type, i, &path);
				Texture texture;
				texture.id = TextureFromFile(path.C_Str(), directory);
				texture.type = typeName;
				texture.path = path.C_Str();
				textures.push_back(texture);
			}
			return textures;
		}

		unsigned int TextureFromFile(const char* path, string directory) 
		{
			string fileName = string(path);
			fileName = directory + "/" + fileName;
			unsigned int ID;
			glGenTextures(1, &ID);

			int width, height, nrComponents;
			unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrComponents, 0);
			if (data)
			{
				GLenum format;
				if (nrComponents == 1) 
				{
					format = GL_RED;
				}else if(nrComponents == 3)
				{
					format = GL_RGB;
				}
				else if (nrComponents == 4) 
				{
					format = GL_RGBA;
				}

				glBindTexture(GL_TEXTURE_2D, ID);
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				stbi_image_free(data);
			}
			else
			{
				cout << "Texture load failed,path:" << fileName << endl;
				stbi_image_free(data);
			}
			
			return ID;
		}
};
#pragma once
#include <string>
using namespace std;

class Texture
{
public:
	unsigned int id;
	string type;
	string path;
	Texture() {}
	Texture(string path,string type);
	~Texture();

private:
	unsigned int TextureFromFile(string path) 
	{
		unsigned int ID;
		glGenTextures(1, &ID);

		int width, height, nrComponent;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponent,0);
		if (data) 
		{
			GLenum format;
			switch (nrComponent)
			{
			case 1:
				format = GL_RED;
			case 3:
				format = GL_RGB;
			case 4:
				format = GL_RGBA;
			}
			glBindTexture(GL_TEXTURE_2D, ID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else 
		{
			cout << "Texture load failed,path:" << path << endl;
		}
		stbi_image_free(data);
		return ID;
	}
};

Texture::Texture(string path,string type)
{
	this->path = path;
	this->type = type;
	this->id = TextureFromFile(this->path);
}

Texture::~Texture()
{
}

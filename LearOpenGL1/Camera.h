#pragma once

//#include <glad/glad.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <functional>
#include <vector>
using namespace std;

enum CameraMoveDir
{
	FORWARD,
	BACK,
	RIGHT,
	LEFT,
	UP,
	DOWN
};

class Camera
{
public:
	static Camera* main;
	glm::vec3 position;
	glm::vec3 world_up;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	float rotateX;
	float rotateY;
	
	float moveSpeed = 1.5f;
	float scrollSpeed = 0.1f;

	float view = 45.0f;
	float width_height_rate = 1920/1080.0f;
	float min = 0.1f;
	float max = 100.0f;

	std::vector<std::function<void()>> on_transform_changed;

	Camera(glm::vec3 pos = glm::vec3(0.0f,0.0f,0.0f),glm::vec3 world_up = glm::vec3(0.0f,1.0f,0.0f),float rotateX = 0.0f,float rotateY = 0.0f):position(pos), world_up(world_up),rotateX(rotateX),rotateY(rotateY)
	{
		update_camera();
	}
	~Camera() 
	{

	}

	void set_camera(float view = 45.0f,float rate = 2.0f,float min = 0.1f,float max = 100.0f) 
	{
		this->view = view;
		this->width_height_rate = rate;
		this->min = min;
		this->max = max;
	}

	glm::mat4 get_view_matrix() 
	{
		return glm::lookAt(position, position + front, up);
	}

	glm::mat4 get_projection_matrix() 
	{
		return glm::perspective(glm::radians(view), width_height_rate, min, max);
	}

	void process_mouse_movement(float xOffset,float yOffset) 
	{
		xOffset *= scrollSpeed;
		yOffset *= scrollSpeed;

		rotateX += yOffset;
		rotateY += xOffset;

		rotateX = (rotateX > 89.0f) ? 89.0f : rotateX;
		rotateX = (rotateX < -89.0) ? -89.0f : rotateX;
		update_camera();
	}

	void process_mouse_scroll(float yOffset) 
	{
		this->view += yOffset;
	}

	void process_keyboard(CameraMoveDir dir,float deltaTime) 
	{
		float velocity = moveSpeed * deltaTime;
		switch (dir)
		{
		case FORWARD:
			position += front * velocity;
			break;
		case BACK:
			position -= front * velocity;
			break;
		case RIGHT:
			position += right * velocity;
			break;
		case LEFT:
			position -= right * velocity;
			break;
		case UP:
			position += up * velocity;
			break;
		case DOWN:
			position -= up * velocity;
			break;
		default:
			break;
		}
		update_camera();
	}

private:
	void update_camera() 
	{
		glm::vec3 front;

		float radianX = glm::radians(rotateX);
		float radianY = glm::radians(rotateY);
		front.y = glm::sin(radianX);

		float projectXZ = glm::cos(radianX);
		front.x = -projectXZ * glm::sin(radianY);
		front.z = projectXZ * glm::cos(radianY);
		
		this->front = glm::normalize(front);
		this->right = glm::normalize(glm::cross(this->front, this->world_up));
		this->up = glm::normalize(glm::cross(this->right, this->front));

		if (!on_transform_changed.empty())
		{
			//for (auto&& e : on_transform_changed)s
			//{
			//	e();
			//}

			for (auto it = on_transform_changed.begin(); it != on_transform_changed.end(); ++it)
			{
				(*it)();
			}
		}
	}
};
Camera* Camera::main = NULL;
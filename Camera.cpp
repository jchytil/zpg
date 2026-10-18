/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Camera.cpp
*/
#include "Camera.h"
#include <cmath>

Camera::Camera(glm::vec3 eye, float aspectRatio)
{
	this->eye = eye;
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	alpha = glm::radians(90.0f);
	fi = glm::radians(270.0f);

	UpdateTarget();
	UpdateViewMatrix();

	projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}

glm::mat4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::UpdateTarget()
{
	target.x = sin(alpha) * cos(fi);
	target.y = cos(alpha);
	target.z = sin(alpha) * sin(fi);
}

glm::mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

void Camera::UpdateViewMatrix()
{
	viewMatrix = glm::lookAt(eye, eye + target, up);
}

void Camera::LookAround(float deltaFi, float deltaAlpha)
{
	fi += deltaFi;
	alpha += deltaAlpha;

	if (fi < 0.0f)
	{
		fi += glm::radians(360.0f);
	}
	if (fi >= glm::radians(360.0f))
	{
		fi -= glm::radians(360.0f);
	}

	if (alpha < glm::radians(1.0f))
	{
		alpha = glm::radians(1.0f);
	}
	if (alpha > glm::radians(179.0f))
	{
		alpha = glm::radians(179.0f);
	}

	UpdateTarget();
	UpdateViewMatrix();
	Notify();
}

void Camera::ToFront()
{
	eye += glm::normalize(target) * speed;
	UpdateViewMatrix();
	Notify();
}

void Camera::ToBack()
{
	eye -= glm::normalize(target) * speed;
	UpdateViewMatrix();
	Notify();
}

void Camera::ToLeft()
{
	eye -= glm::normalize(glm::cross(target, up)) * speed;
	UpdateViewMatrix();
	Notify();
}

void Camera::ToRight()
{
	eye += glm::normalize(glm::cross(target, up)) * speed;
	UpdateViewMatrix();
	Notify();
}

void Camera::SetAspectRatio(float aspectRatio)
{
	projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	Notify();
}
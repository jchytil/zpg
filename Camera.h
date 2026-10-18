/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Camera.h
*/
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Subject.h"

class Camera : public Subject
{
private:
	glm::vec3 eye;
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;

	float alpha;
	float fi;

	float speed = 0.02f;

	float fov = 60.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;

	void UpdateTarget();
	void UpdateViewMatrix();

public:
	Camera(glm::vec3 eye, float aspectRatio);

	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix();

	void LookAround(float deltaFi, float deltaAlpha);

	void ToFront();
	void ToBack();
	void ToLeft();
	void ToRight();

	void SetAspectRatio(float aspectRatio);
};
/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Transformation.h
*/
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformation
{
public:
	virtual glm::mat4 GetMatrix() = 0;
	virtual void Update(float time) 
	{

	}
	virtual ~Transformation() = default;
};
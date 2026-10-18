/*
* Author: Jakub Chytil
* Login: CHY0105
* File: DrawableObject.h
*/
#pragma once
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"

class DrawableObject
{
private:
	ShaderProgram* shaderProgram;
	Model* model;
	Transformation* transformation;

public:
	DrawableObject(ShaderProgram* shaderProgram, Model* model, Transformation* transformation);

	void Draw();
	void Update(float time);
};
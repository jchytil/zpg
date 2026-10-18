/*
* Author: Jakub Chytil
* Login: CHY0105
* File: DrawableObject.cpp
*/
#include "DrawableObject.h"

DrawableObject::DrawableObject(ShaderProgram* shaderProgram, Model* model, Transformation* transformation)
{
	this->shaderProgram = shaderProgram;
	this->model = model;
	this->transformation = transformation;
}

void DrawableObject::Draw() 
{
	if (!shaderProgram->SetShaderProgram())
	{
		return;
	}

	shaderProgram->SetUniform("modelMatrix", transformation->GetMatrix());

	glBindVertexArray(model->GetVAO());

	glDrawArrays(GL_TRIANGLES, 0, model->GetVertexCount());

	glUseProgram(0);
}

void DrawableObject::Update(float time)
{
	transformation->Update(time);
}
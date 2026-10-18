/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Model.cpp
*/
#include "Model.h"

Model::Model()
{
	VBO = 0;
	VAO = 0;
	vertexCount = 0;
}

void Model::CreateModel(const float* points, int size, const std::vector<int>& attributeSizes)
{
	CreateVBO(points, size, attributeSizes);
	CreateVAO(attributeSizes);
}

void Model::CreateVBO(const float* points, int size, const std::vector<int>& attributeSizes)
{
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, points, GL_STATIC_DRAW);

	int sizeSum = 0;
	for (int attributeSize : attributeSizes)
	{
		sizeSum += attributeSize;
	}

	vertexCount = size / (sizeSum * sizeof(float));
}

void Model::CreateVAO(const std::vector<int>& attributeSizes)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	int sizeSum = 0;
	for (int attributeSize : attributeSizes)
	{
		sizeSum += attributeSize;
	}

	int currentOffset = 0;
	for (int i = 0; i < attributeSizes.size(); i++)
	{
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, attributeSizes[i], GL_FLOAT, GL_FALSE, sizeSum * sizeof(float), (GLvoid*)(currentOffset * sizeof(float)));

		currentOffset += attributeSizes[i];
	}
}

int Model::GetVertexCount()
{
	return vertexCount;
}

GLuint Model::GetVBO()
{
	return VBO;
}

GLuint Model::GetVAO()
{
	return VAO;
}
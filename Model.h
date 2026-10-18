/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Model.h
*/
#pragma once
#include <glad/gl.h>
#include <vector>

class Model 
{
private:
    GLuint VBO;
    GLuint VAO;
    int vertexCount;
    void CreateVBO(const float* points, int size, const std::vector<int>& attributeSizes);
    void CreateVAO(const std::vector<int>& attributeSizes);
public:
    Model();
    void CreateModel(const float* points, int size, const std::vector<int>& attributeSizes);
    GLuint GetVAO();
    GLuint GetVBO();
    int GetVertexCount();
};
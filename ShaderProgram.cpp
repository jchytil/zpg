/*
* Author: Jakub Chytil
* Login: CHY0105
* File: ShaderProgram.cpp
*/
#include "ShaderProgram.h"
#include "Camera.h"

ShaderProgram::ShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId) 
{
    id = glCreateProgram();
    glAttachShader(id, vertexShaderId);
    glAttachShader(id, fragmentShaderId);
    glLinkProgram(id);
}

bool ShaderProgram::SetShaderProgram()
{
    if (id == 0)
    {
        return false;
    }
    glUseProgram(id);
    return true;
}

GLuint ShaderProgram::GetId() 
{
    return id; 
}

void ShaderProgram::SetUniform(const char* name, float value) 
{
    GLint location = glGetUniformLocation(id, name);
    if (location != -1)
    {
        glUniform1f(location, value);
    }
}

void ShaderProgram::SetUniform(const char* name, float x, float y, float z) 
{
    GLint location = glGetUniformLocation(id, name);
    if (location != -1)
    {
        glUniform3f(location, x, y, z);
    }
}

void ShaderProgram::SetUniform(const char* name, const glm::mat4& matrix) 
{
    GLint matrixLocation = glGetUniformLocation(id, name);

    if (matrixLocation != -1) 
    {
        glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }
}

void ShaderProgram::SetCamera(Camera* camera)
{
    this->camera = camera;
    camera->Attach(this);
    Update();
}

void ShaderProgram::Update()
{
    glUseProgram(id);
    SetUniform("viewMatrix", camera->GetViewMatrix());
    SetUniform("projectionMatrix", camera->GetProjectionMatrix());
    glUseProgram(0);
}
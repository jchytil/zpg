/*
* Author: Jakub Chytil
* Login: CHY0105
* File: ShaderProgram.h
*/
#pragma once
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Observer.h"

class Camera;

class ShaderProgram : public Observer
{
private:
    GLuint id;
    Camera* camera = nullptr;

public:
    ShaderProgram(GLuint vertexShaderId, GLuint fragmentShaderId);
    bool SetShaderProgram();
    GLuint GetId();

    void SetUniform(const char* name, float value);
    void SetUniform(const char* name, float x, float y, float z);
    void SetUniform(const char* name, const glm::mat4& matrix);
    void SetCamera(Camera* camera);
    void Update() override;
};
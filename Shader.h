/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Shader.h
*/
#pragma once
#include <glad/gl.h>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>

class Shader 
{
public:
    GLuint Create(GLenum shaderType, const char* shaderFile);
};
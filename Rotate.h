/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Rotate.h
*/
#pragma once
#include "Transformation.h"

class Rotate : public Transformation 
{
private:
    float angle;
    glm::vec3 axis;
public:
    Rotate(float a, glm::vec3 ax) : angle(a), axis(ax) 
    {

    }

    void SetAngle(float a) 
    { 
        angle = a; 
    }

    void AddAngle(float a) 
    { 
        angle += a; 
    }

    glm::mat4 GetMatrix() override 
    {
        return glm::rotate(glm::mat4(1.0f), angle, axis);
    }
};
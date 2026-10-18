/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Scale.h
*/
#pragma once
#include "Transformation.h"

class Scale : public Transformation 
{
private:
    glm::vec3 scale;
public:
    Scale(glm::vec3 s) : scale(s) 
    {

    }

    void SetScale(glm::vec3 s) 
    { 
        scale = s; 
    }

    void AddScale(glm::vec3 s) 
    { 
        scale += s; 
    }

    glm::mat4 GetMatrix() override 
    {
        return glm::scale(glm::mat4(1.0f), scale);
    }
};
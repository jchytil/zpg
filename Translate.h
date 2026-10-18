/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Translate.h
*/
#pragma once
#include "Transformation.h"

class Translate : public Transformation 
{
private:
    glm::vec3 translation;
public:
    Translate(glm::vec3 t) : translation(t) 
    {

    }

    void AddTranslation(glm::vec3 t) 
    { 
        translation += t; 
    }

    glm::mat4 GetMatrix() override 
    {
        return glm::translate(glm::mat4(1.0f), translation);
    }
};
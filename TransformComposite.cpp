/*
* Author: Jakub Chytil
* Login: CHY0105
* File: TransformComposite.cpp
*/
#include "TransformComposite.h"

void TransformComposite::Add(Transformation* transformation) 
{
    transformations.push_back(transformation);
}

glm::mat4 TransformComposite::GetMatrix() 
{
    glm::mat4 finalMatrix = glm::mat4(1.0f);

    for (Transformation* t : transformations) 
    {
        finalMatrix *= t->GetMatrix();
    }

    return finalMatrix;
}

void TransformComposite::Update(float time)
{
    for (Transformation* t : transformations)
    {
        t->Update(time);
    }
}
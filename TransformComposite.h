/*
* Author: Jakub Chytil
* Login: CHY0105
* File: TransformComposite.h
*/
#pragma once
#include "Transformation.h"
#include <vector>

class TransformComposite : public Transformation 
{
private:
    std::vector<Transformation*> transformations;
public:
    void Add(Transformation* transformation);
    glm::mat4 GetMatrix() override;
    void Update(float time) override;
};
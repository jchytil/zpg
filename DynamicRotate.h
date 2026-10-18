/*
* Author: Jakub Chytil
* Login: CHY0105
* File: DynamicRotate.h
*/
#pragma once
#include "Rotate.h"

class DynamicRotate : public Rotate
{
private:
    float speed;
    float startAngle;
public:
    DynamicRotate(float speed, glm::vec3 axis, float startAngle = 0.0f) : Rotate(startAngle, axis), speed(speed), startAngle(startAngle)
    {
        
    }

    void Update(float time) override
    {
        SetAngle(startAngle + speed * time);
    }
};
/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Scene.h
*/
#pragma once
#include <vector>
#include "DrawableObject.h"

class Scene
{
private:
	std::vector<DrawableObject*> objects;

public:
	void AddObject(DrawableObject* object);
	void Render();
	void Update(float time);
};
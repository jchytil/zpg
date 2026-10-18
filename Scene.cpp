/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Scene.cpp
*/
#include "Scene.h"

void Scene::AddObject(DrawableObject* object) 
{
	objects.push_back(object);
}

void Scene::Render() 
{
	for (DrawableObject* object : objects)
	{
		object->Draw();
	}
}

void Scene::Update(float time)
{
	for (DrawableObject* object : objects)
	{
		object->Update(time);
	}
}
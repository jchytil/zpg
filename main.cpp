/*
* Author: Jakub Chytil
* Login: CHY0105
* File: main.cpp
*/
#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION
#include "Application.h"

int main(void)
{
	Application app;

	app.CreateShaders();
	app.CreateModels();
	app.CreateScenes();
	app.Run();

	return 0;
}
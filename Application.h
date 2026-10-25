/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Application.h
*/
#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "models/triangle.h"
#include "models/sphere.h"
#include "models/bushes.h"
#include "models/tree.h"
#include "models/login.h"
#include "models/sun.h"
#include "models/earth.h"
#include "models/moon.h"
#include "models/rocket.h"

#include "Shader.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "Transformation.h"
#include "DrawableObject.h"
#include "Scene.h"
#include "TransformComposite.h"
#include "Translate.h"
#include "Rotate.h"
#include "Scale.h"
#include "DynamicRotate.h"
#include <random>
#include "Camera.h"
#include "models/clock.h"
#include <ctime>
#include "models/plain.h"

class Application
{
private:
	GLFWwindow* window;
	int currentSceneIndex = 0;

	ShaderProgram* shaderProgram = nullptr;
	ShaderProgram* colorShaderProgram = nullptr;
	ShaderProgram* treeShaderProgram = nullptr;
	ShaderProgram* sunShaderProgram = nullptr;
	ShaderProgram* bushShaderProgram = nullptr;
	ShaderProgram* plainShaderProgram = nullptr;

	ShaderProgram* constantShaderProgram;
	ShaderProgram* lambertShaderProgram;
	ShaderProgram* phongShaderProgram;
	ShaderProgram* blinnShaderProgram;

	ShaderProgram* constantColorShaderProgram;
	ShaderProgram* phongColorShaderProgram;
	ShaderProgram* blinnColorShaderProgram;

	std::vector<Model*> models;
	std::vector<Transformation*> transformations;
	std::vector<DrawableObject*> objects;
	std::vector<Scene*> scenes;

	Model* modelTriangle = nullptr;
	Model* modelSphere = nullptr;
	Model* modelBushes = nullptr;
	Model* modelTree = nullptr;
	Model* modelLogin = nullptr;
	Model* modelSun = nullptr;
	Model* modelEarth = nullptr;
	Model* modelMoon = nullptr;
	Model* modelPlain = nullptr;
	Model* modelRocket = nullptr;

	Transformation* moveTransformation = nullptr;
	Transformation* loginTransformation = nullptr;

	Translate* moveTranslate;
	Rotate* moveRotate;
	Scale* moveScale;
	Camera* camera = nullptr;

	double lastMouseX = 0.0;
	double lastMouseY = 0.0;

	Model* modelClock = nullptr;
	ShaderProgram* clockShaderProgram = nullptr;


	Model* AddModel(const float* points, int size, const std::vector<int>& attributeSizes = { 3, 3 });
	Transformation* AddTransformation(Transformation* transformation);
	DrawableObject* AddObject(Model* model, Transformation* transformation, ShaderProgram* customShader = nullptr);
	Scene* AddScene();

	bool Initialize();
	void ProcessInput();
	void Update();

	void CreateTriangleScene(DrawableObject* signature);
	void CreateSphereScene(DrawableObject* signature);
	void CreateForestScene(DrawableObject* signature);
	void CreateLoginScene(DrawableObject* signature);
	void CreateSolarSystemScene(DrawableObject* signature);
	void CreateLightScene(DrawableObject* signature);
	void ResizeWindow(int width, int height);
	void UpdateClock();
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

public:
	Application();
	~Application();

	void CreateShaders();
	void CreateModels();
	void CreateScenes();
	void Run();
};
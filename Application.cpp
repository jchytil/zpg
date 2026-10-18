/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Application.cpp
*/
#include "Application.h"

Application::Application()
{
	if (!Initialize())
	{
		exit(EXIT_FAILURE);
	}
}

Application::~Application()
{
	for (Scene* scene : scenes)
	{
		delete scene;
	}

	for (DrawableObject* object : objects)
	{
		delete object;
	}

	for (Transformation* transformation : transformations)
	{
		delete transformation;
	}

	for (Model* model : models)
	{
		delete model;
	}

	delete shaderProgram;
	delete sunShaderProgram;

	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Application::Initialize() 
{
	if (!glfwInit())
	{
		return false;
	}

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glfwSwapInterval(1);

	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		return false;
	}
	glEnable(GL_DEPTH_TEST);
	return true;
}

Model* Application::AddModel(const float* points, int size, const std::vector<int>& attributeSizes)
{
	Model* model = new Model();
	model->CreateModel(points, size, attributeSizes);
	models.push_back(model);
	return model;
}

Transformation* Application::AddTransformation(Transformation* transformation)
{
	transformations.push_back(transformation);
	return transformation;
}

DrawableObject* Application::AddObject(Model* model, Transformation* transformation, ShaderProgram* customShader) 
{
	ShaderProgram* sp = (customShader != nullptr) ? customShader : shaderProgram;
	DrawableObject* object = new DrawableObject(sp, model, transformation);
	objects.push_back(object);
	return object;
}

Scene* Application::AddScene() 
{
	Scene* scene = new Scene();
	scenes.push_back(scene);
	return scene;
}

void Application::CreateShaders() 
{
	Shader shader;

	GLuint vertexShader = shader.Create(GL_VERTEX_SHADER, "shaders/basic.vert");
	GLuint fragmentShader = shader.Create(GL_FRAGMENT_SHADER, "shaders/basic.frag");
	GLuint sunFragShader = shader.Create(GL_FRAGMENT_SHADER, "shaders/sun.frag");

	shaderProgram = new ShaderProgram(vertexShader, fragmentShader);
	sunShaderProgram = new ShaderProgram(vertexShader, sunFragShader);

	GLuint colorVertShader = shader.Create(GL_VERTEX_SHADER, "shaders/color.vert");
	GLuint colorFragShader = shader.Create(GL_FRAGMENT_SHADER, "shaders/color.frag");
	colorShaderProgram = new ShaderProgram(colorVertShader, colorFragShader);

	GLuint clockVertShader = shader.Create(GL_VERTEX_SHADER, "shaders/clock.vert");
	clockShaderProgram = new ShaderProgram(clockVertShader, colorFragShader);

	GLuint treeVertShader = shader.Create(GL_VERTEX_SHADER, "shaders/tree.vert");
	GLuint treeFragShader = shader.Create(GL_FRAGMENT_SHADER, "shaders/tree.frag");
	treeShaderProgram = new ShaderProgram(treeVertShader, treeFragShader);

	GLuint bushFragShader = shader.Create(GL_FRAGMENT_SHADER, "shaders/bush.frag");
	bushShaderProgram = new ShaderProgram(vertexShader, bushFragShader);

	GLuint plainFragShader = shader.Create(GL_FRAGMENT_SHADER, "shaders/plain.frag");
	plainShaderProgram = new ShaderProgram(vertexShader, plainFragShader);

	camera = new Camera(glm::vec3(0.0f, 0.0f, 2.0f), 800.0f / 600.0f);
	shaderProgram->SetCamera(camera);
	sunShaderProgram->SetCamera(camera);
	colorShaderProgram->SetCamera(camera);
	clockShaderProgram->SetCamera(camera);
	treeShaderProgram->SetCamera(camera);
	bushShaderProgram->SetCamera(camera);
	plainShaderProgram->SetCamera(camera);

}

void Application::CreateModels() 
{
	modelTriangle = AddModel(triangle, sizeof(triangle));
	modelSphere = AddModel(sphere, sizeof(sphere));
	modelBushes = AddModel(bushes, sizeof(bushes));
	modelTree = AddModel(tree, sizeof(tree));
	modelLogin = AddModel(login, sizeof(login));
	modelSun = AddModel(sun, sizeof(sun), { 3, 3, 3 });
	modelEarth = AddModel(earth, sizeof(earth), { 3, 3, 3 });
	modelMoon = AddModel(moon, sizeof(moon), { 3, 3, 3 });
	modelClock = AddModel(clockModel, sizeof(clockModel), { 3, 3, 3 });
	modelPlain = AddModel(plain, sizeof(plain));
}

void Application::CreateScenes() 
{
	moveTranslate = new Translate(glm::vec3(0.0f));
	moveRotate = new Rotate(0.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	moveScale = new Scale(glm::vec3(1.0f));

	TransformComposite* moveComposite = new TransformComposite();
	moveComposite->Add(moveTranslate);
	moveComposite->Add(moveRotate);
	moveComposite->Add(moveScale);

	moveTransformation = moveComposite;
	transformations.push_back(moveComposite);

	TransformComposite* loginComposite = new TransformComposite();
	loginComposite->Add(new Translate(glm::vec3(-0.5f, -0.85f, 0.0f)));
	loginComposite->Add(new Scale(glm::vec3(0.2f, 0.2f, 0.2f)));
	loginTransformation = loginComposite;
	transformations.push_back(loginComposite);

	DrawableObject* signature = AddObject(modelLogin, loginTransformation);

	CreateTriangleScene(signature);
	CreateSphereScene(signature);
	CreateForestScene(signature);
	CreateLoginScene(signature);
	CreateSolarSystemScene(signature);
}

void Application::CreateTriangleScene(DrawableObject* signature) 
{
	Scene* scene = AddScene();

	TransformComposite* staticComposite = new TransformComposite();
	staticComposite->Add(new Translate(glm::vec3(-0.5f, 0.5f, 0.0f)));
	staticComposite->Add(new Rotate(0.5f, glm::vec3(0.0f, 0.0f, 1.0f)));
	staticComposite->Add(new Scale(glm::vec3(0.3f)));
	scene->AddObject(AddObject(modelTriangle, staticComposite));

	TransformComposite* dynamicComposite = new TransformComposite();
	dynamicComposite->Add(new Translate(glm::vec3(0.5f, 0.5f, 0.0f)));
	dynamicComposite->Add(new DynamicRotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
	dynamicComposite->Add(new Scale(glm::vec3(0.3f)));
	scene->AddObject(AddObject(modelTriangle, dynamicComposite));

	TransformComposite* orderTRS = new TransformComposite();
	orderTRS->Add(new Translate(glm::vec3(0.6f, 0.0f, 0.0f)));
	orderTRS->Add(new Rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f)));
	orderTRS->Add(new Scale(glm::vec3(0.3f)));
	scene->AddObject(AddObject(modelTriangle, orderTRS));

	TransformComposite* orderRTS = new TransformComposite();
	orderRTS->Add(new Rotate(1.57f, glm::vec3(0.0f, 0.0f, 1.0f)));
	orderRTS->Add(new Translate(glm::vec3(0.6f, 0.0f, 0.0f)));
	orderRTS->Add(new Scale(glm::vec3(0.3f)));
	scene->AddObject(AddObject(modelTriangle, orderRTS));

	scene->AddObject(signature);
	scene->AddObject(AddObject(modelTriangle, moveTransformation));
}

void Application::CreateSphereScene(DrawableObject* signature) 
{
	Scene* scene = AddScene();
	scene->AddObject(AddObject(modelSphere, moveTransformation));
	scene->AddObject(signature);
}

void Application::CreateForestScene(DrawableObject* signature)
{
	Scene* scene = AddScene();

	TransformComposite* plainComposite = new TransformComposite();
	plainComposite->Add(new Translate(glm::vec3(0.0f, -1.0f, -10.0f)));
	plainComposite->Add(new Scale(glm::vec3(12.0f, 1.0f, 12.0f)));
	scene->AddObject(AddObject(modelPlain, plainComposite, plainShaderProgram));

	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> posX(-10.0f, 10.0f);
	std::uniform_real_distribution<float> posZ(-20.0f, 0.0f);
	std::uniform_real_distribution<float> angle(0.0f, 6.28f);
	std::uniform_real_distribution<float> treeScale(0.2f, 0.35f);
	std::uniform_real_distribution<float> bushScale(1.0f, 2.0f);

	for (int i = 0; i < 74; i++)
	{
		TransformComposite* treeComposite = new TransformComposite();
		treeComposite->Add(new Translate(glm::vec3(posX(rng), -1.0f, posZ(rng))));
		treeComposite->Add(new Rotate(angle(rng), glm::vec3(0.0f, 1.0f, 0.0f)));
		treeComposite->Add(new Scale(glm::vec3(treeScale(rng))));
		scene->AddObject(AddObject(modelTree, treeComposite, treeShaderProgram));
	}

	for (int i = 0; i < 12; i++)
	{
		TransformComposite* bushComposite = new TransformComposite();
		bushComposite->Add(new Translate(glm::vec3(posX(rng), -1.0f, posZ(rng))));
		bushComposite->Add(new Rotate(angle(rng), glm::vec3(0.0f, 1.0f, 0.0f)));
		bushComposite->Add(new Scale(glm::vec3(bushScale(rng))));
		scene->AddObject(AddObject(modelBushes, bushComposite, bushShaderProgram));
	}

	TransformComposite* sunComposite = new TransformComposite();
	sunComposite->Add(new Translate(glm::vec3(8.0f, 10.0f, -30.0f)));
	sunComposite->Add(new Scale(glm::vec3(3.0f)));

	TransformComposite* clock1Composite = new TransformComposite();
	clock1Composite->Add(new Translate(glm::vec3(-3.0f, 0.0f, -5.0f)));
	clock1Composite->Add(new Scale(glm::vec3(-1.f, 1.f, 1.f)));
	clock1Composite->Add(new Rotate(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	scene->AddObject(AddObject(modelClock, clock1Composite, clockShaderProgram));

	TransformComposite* clock2Composite = new TransformComposite();
	clock2Composite->Add(new Translate(glm::vec3(4.0f, 0.0f, -12.0f)));
	clock2Composite->Add(new Scale(glm::vec3(-1.f, 1.f, 1.f)));
	clock2Composite->Add(new Rotate(glm::radians(150.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	scene->AddObject(AddObject(modelClock, clock2Composite, clockShaderProgram));

	scene->AddObject(AddObject(modelSphere, sunComposite, sunShaderProgram));
	scene->AddObject(signature);
}

void Application::CreateLoginScene(DrawableObject* signature) 
{
	Scene* scene = AddScene();
	scene->AddObject(AddObject(modelLogin, moveTransformation));
	scene->AddObject(signature);
}

void Application::CreateSolarSystemScene(DrawableObject* signature)
{
	Scene* scene = AddScene();

	TransformComposite* sunComposite = new TransformComposite();
	sunComposite->Add(new DynamicRotate(0.5f, glm::vec3(0.0f, 0.0f, 1.0f)));
	sunComposite->Add(new Scale(glm::vec3(0.2f)));
	scene->AddObject(AddObject(modelSun, sunComposite, colorShaderProgram));

	TransformComposite* earthOrbit = new TransformComposite();
	earthOrbit->Add(new DynamicRotate(0.5f, glm::vec3(0.0f, 0.0f, 1.0f)));
	earthOrbit->Add(new Translate(glm::vec3(0.6f, 0.0f, 0.0f)));

	TransformComposite* earthComposite = new TransformComposite();
	earthComposite->Add(earthOrbit);
	earthComposite->Add(new Scale(glm::vec3(0.08f)));
	scene->AddObject(AddObject(modelEarth, earthComposite, colorShaderProgram));

	TransformComposite* moonComposite = new TransformComposite();
	moonComposite->Add(earthOrbit);
	moonComposite->Add(new DynamicRotate(2.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
	moonComposite->Add(new Translate(glm::vec3(0.15f, 0.0f, 0.0f)));
	moonComposite->Add(new Scale(glm::vec3(0.03f)));
	scene->AddObject(AddObject(modelMoon, moonComposite, colorShaderProgram));

	scene->AddObject(signature);
}

void Application::ProcessInput() 
{
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && scenes.size() > 0)
	{
		currentSceneIndex = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && scenes.size() > 1)
	{
		currentSceneIndex = 1;
	}

	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && scenes.size() > 2)
	{
		currentSceneIndex = 2;
	}

	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && scenes.size() > 3)
	{
		currentSceneIndex = 3;
	}

	if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && scenes.size() > 4)
	{
		currentSceneIndex = 4;
	}

}

void Application::Update()
{
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		moveTranslate->AddTranslation(glm::vec3(0.01f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		moveTranslate->AddTranslation(glm::vec3(-0.01f, 0.0f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		moveTranslate->AddTranslation(glm::vec3(0.0f, 0.01f, 0.0f));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		moveTranslate->AddTranslation(glm::vec3(0.0f, -0.01f, 0.0f));
	}

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		moveRotate->AddAngle(0.05f);
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		moveRotate->AddAngle(-0.05f);
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
	{
		moveScale->AddScale(glm::vec3(0.01f, 0.01f, 0.01f));
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		moveScale->AddScale(glm::vec3(-0.01f, -0.01f, -0.01f));
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->ToFront();
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->ToBack();
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->ToLeft();
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->ToRight();
	}

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		float dx = (float)(mouseX - lastMouseX);
		float dy = (float)(mouseY - lastMouseY);
		camera->LookAround(dx * 0.005f, dy * 0.005f);
	}

	lastMouseX = mouseX;
	lastMouseY = mouseY;

	UpdateClock();
}

void Application::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Application* app = (Application*)glfwGetWindowUserPointer(window);

	if (width > 0 && height > 0 && app->camera != nullptr)
	{
		app->ResizeWindow(width, height);
	}
}

void Application::ResizeWindow(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetAspectRatio((float)width / (float)height);
}

void Application::UpdateClock()
{
	time_t now = time(nullptr);
	tm local;
	localtime_s(&local, &now);

	float seconds = (float)local.tm_sec;
	float minutes = (float)local.tm_min + seconds / 60.0f;
	float hours = (float)(local.tm_hour % 12) + minutes / 60.0f;

	clockShaderProgram->SetShaderProgram();
	clockShaderProgram->SetUniform("secondAngle", seconds / 60.0f * glm::radians(360.0f));
	clockShaderProgram->SetUniform("minuteAngle", minutes / 60.0f * glm::radians(360.0f));
	clockShaderProgram->SetUniform("hourAngle", hours / 12.0f * glm::radians(360.0f));
	glUseProgram(0);
}

void Application::Run() 
{
	glfwGetCursorPos(window, &lastMouseX, &lastMouseY);

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput();
		Update();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (!scenes.empty())
		{
			scenes[currentSceneIndex]->Update((float)glfwGetTime());
			scenes[currentSceneIndex]->Render();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
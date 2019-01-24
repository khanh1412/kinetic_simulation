#include"Engine.h"
#include<iostream>
Engine::Engine(int Width, int Height, const std::string& name)
	: Width(Width), Height(Height), name(name), pov(0)
{
	if (!glfwInit())
	{
		std::cout<<"glfwInit failed!"<<std::endl;
		__builtin_trap();
		return;
	}

	window = glfwCreateWindow(Width, Height, name.c_str(), nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		std::cout<<"window creation failed!"<<std::endl;
		__builtin_trap();
		return;
	}
	else
	{
		std::cout<<"window created "<<Width<<"x"<<Height<<std::endl;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
	{
		std::cout<< "GLEW Error!"<<std::endl;
		__builtin_trap();
	}

	std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
Engine::~Engine()
{
	glfwTerminate();
}

bool Engine::isClosed()
{
	return glfwWindowShouldClose(window);
}

void Engine::clear()
{
	renderer.Clear();
}
void Engine::swapBuffers()
{
	glfwSwapBuffers(window);
}
void Engine::waitEvents()
{
	glfwWaitEvents();
}
void Engine::pollEvents()
{
	glfwPollEvents();
}

void Engine::setCam(float x, float y, float z)
{
	cam = {x, y, z};
}
void Engine::setCenter(float x, float y, float z)
{
	center = {x, y, z};
}
void Engine::setUp(float x, float y, float z)
{
	up = {x, y, z};
}
void Engine::setPov(float a)
{
	pov = a;
}

void Engine::draw(Object *obj)
{
	auto va		= obj->getVertexArray();	va->Bind();
	auto ib		= obj->getIndexBuffer(cam);	ib->Bind();
	auto shader	= obj->getShader();		shader->Bind();
	auto texture	= obj->getTexture();		texture->Bind();

	glm::mat4 Proj, View, Model(1.0f);
	Proj = glm::perspective(pov, static_cast<float>(Width)/static_cast<float>(Height), 0.0f, 1000.0f);
	View = glm::lookAt(cam, center, up);
	Model = glm::translate(Model, obj->getShift());
	Model = glm::rotate(Model, obj->getRotate()[0], glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::rotate(Model, obj->getRotate()[1], glm::vec3(0.0f, 1.0f, 0.0f));
	Model = glm::rotate(Model, obj->getRotate()[2], glm::vec3(0.0f, 0.0f, 1.0f));
	Model = glm::scale(Model, obj->getScale());

	glm::mat4 MVP = Proj * View * Model;

	shader->SetUniformMat4f("u_MVP", MVP);

	renderer.Draw(*va, *ib, *shader);
}
void Engine::draw(std::vector<Object*> *objs)
{
	for (int i=0; i<objs->size(); i++)
		draw(objs->at(i));
}

GLFWwindow *Engine::getWindow()
{
	return window;
}

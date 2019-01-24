#include"Engine.h"
#include<iostream>
Object::Object(bool vb_dynamic, bool ib_dynamic)
	: va(nullptr), vb(nullptr), layout(nullptr), ib(nullptr), s(nullptr), t(nullptr),
	Shift({0,0,0}), Rotate({0,0,0}), Scale({1,1,1}),
	vb_dynamic(vb_dynamic), ib_dynamic(ib_dynamic),
	positions(nullptr), indices(nullptr)
{}
Object::~Object()
{
	delete va;
	delete vb;
	delete layout;
	delete ib;
	delete s;
	delete t;
	delete positions;
	delete indices;
}

void Object::genShader(const std::string& path)
{
	if (s) delete s;
	s = new Shader(path);
}
void Object::genTexture(const std::string& path)
{
	if (s == nullptr)
		genShader("./resources/shaders/math.shader");

	if (t) delete t;
	s->Bind();
	t = new Texture(path);
}

VertexArray *Object::getVertexArray()
{
	if (va == nullptr) //create VertexArray
	{
		va = new VertexArray();
		genPositions();
		genLayout();
		if (vb_dynamic)
			vb = new VertexBuffer(size);
		else
			vb = new VertexBuffer(positions, size);
		va->AddBuffer(*vb, *layout);
	}
	if (vb_dynamic) //Refresh if dynamic
	{
		genPositions();
		vb->setData(positions, size);
	}
	return va;
}
IndexBuffer *Object::getIndexBuffer(glm::vec3& cam)
{
	if (ib == nullptr) //create IndexBuffer
	{
		genIndices(cam);
		if (ib_dynamic)
			ib = new IndexBuffer(count);
		else
			ib = new IndexBuffer(indices, count);
	}
	if (ib_dynamic) //Refresh if dynamic
	{
		genIndices(cam);
		ib->setData(indices, count);
	}
	return ib;
}
Shader *Object::getShader()
{
	if (s == nullptr)
	{
		genShader("./resources/shaders/math.shader");
		genTexture("./resources/textures/a.png");	
	}
	return s;
}
Texture *Object::getTexture()
{
	if (t == nullptr)
		genTexture("./resources/textures/a.png");
	return t;
}

void Object::setShift(float x, float y, float z)
{
	Shift = {x, y, z};
}
void Object::setRotate(float x, float y, float z)
{
	Rotate = {x, y, z};
}
void Object::setScale(float x, float y, float z)
{
	Scale = {x, y, z};
}
void Object::shift(float x, float y, float z)
{
	Shift += glm::vec3({x, y, z});
}
void Object::rotate(float x, float y, float z)
{
	Rotate += glm::vec3({x, y, z});
}
void Object::scale(float x, float y, float z)
{
	Scale += glm::vec3({x, y, z});
}
glm::vec3& Object::getShift()
{
	return Shift;
}
glm::vec3& Object::getRotate()
{
	return Rotate;
}
glm::vec3& Object::getScale()
{
	return Scale;
}


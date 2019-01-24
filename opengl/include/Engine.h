#ifndef _ENGINE_H_
#define _ENGINE_H_

#include"GL/glew.h"
#include"GLFW/glfw3.h"

#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include"Texture.h"

#include"glm/ext.hpp"


#include<string>

class Object
{
	protected:
		VertexArray *va;
		VertexBuffer *vb;
		bool vb_dynamic;
		VertexBufferLayout *layout;
		IndexBuffer *ib;
		bool ib_dynamic;
		Shader *s;
		Texture *t;

		float *positions;
		unsigned int size;
		unsigned int *indices;
		unsigned int count;

		glm::vec3 Shift;
		glm::vec3 Rotate;
		glm::vec3 Scale;
		
		//gen VertexBufferLayout
		virtual void genLayout()=0;
	public:
		//gen positions and size
		virtual void genPositions()=0;
		//gen indices and count
		virtual void genIndices(glm::vec3& cam)=0;

	public:
		Object(bool vb_dynamic, bool ib_dynamic);
		~Object();
		
		VertexArray *getVertexArray();
		IndexBuffer *getIndexBuffer(glm::vec3& cam);
		Shader *getShader();
		Texture *getTexture();

		//gen Shader
		void genShader(const std::string& path);
		//gen Texture
		void genTexture(const std::string& path);

		void setShift(float x, float y, float z);
		void setRotate(float x, float y, float z);
		void setScale(float x, float y, float z);
		void shift(float x, float y, float z);
		void rotate(float x, float y, float z);
		void scale(float x, float y, float z);
		glm::vec3& getShift();
		glm::vec3& getRotate();
		glm::vec3& getScale();

};
class Engine
{
	private:
		Renderer renderer;
		GLFWwindow *window;
		int Width, Height;
		std::string name;

		glm::vec3 cam;
		glm::vec3 center;
		glm::vec3 up;
		float pov;

	public:
		Engine(int Width, int Height, const std::string &name);
		~Engine();
		bool isClosed();
		void clear();
		void swapBuffers();
		void waitEvents();
		void pollEvents();

		void draw(Object *obj);
		void draw(std::vector<Object*> *objs);
		void setCam(float x, float y, float z);
		void setCenter(float x, float y, float z);
		void setUp(float x, float y, float z);
		void setPov(float a);

		GLFWwindow *getWindow();
};

#endif

#include"GL/glew.h"
#include"GLFW/glfw3.h"
#include<iostream>


#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include"Texture.h"


#include<cmath>
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"

#define HEIGHT 640
#define WIDTH 640

int main(void)
{
	//intialize the library
	
	if (!glfwInit())
		return -1;

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", nullptr, nullptr);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout<< "Error!"<<std::endl;

	std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<std::endl;

{


	float positions[] = 
	{
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,//bottom left
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,//bottom right
		 0.0f, -1.0f,-1.0f, 0.5f, 0.0f,//bottom middle
		 0.0f,  1.0f,-1.0f, 0.5f, 1.0f,//top middle
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,//top right
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f //top left
	};

	unsigned int indices1[] =
	{
		0, 2, 5,
		2, 3, 5,
		2, 1, 3,
		3, 4, 1
	};
	unsigned int indices2[] =
	{
		1, 2, 4,
		2, 3, 4,
		2, 0, 3,
		3, 5, 0
	};

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	VertexArray va;
	VertexBuffer vb(positions, 30*sizeof(float));
	VertexBufferLayout layout;
	layout.Push_float(3);//2 floats of rectangle vertices
	layout.Push_float(2);//2 floats of texture coordinates

	va.AddBuffer(vb, layout);

	IndexBuffer ib1(indices1, 12);
	IndexBuffer ib2(indices2, 12);

	//glm::mat4 P = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glm::mat4 P = glm::perspective(1.5708f, (float)HEIGHT / (float)WIDTH, 1.0f, 100.0f);
	glm::mat4 V = glm::lookAt( glm::vec3( 0.f, 0.f, 2.0f ),glm::vec3( 0.f, 0.f, 0.f ),glm::vec3( 0.0f, -1.0f, 0.0f)); 
	glm::mat4 MVP	= P*V;




	Shader shader("./resources/shaders/math.shader");
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", MVP);

	Texture texture("./resources/textures/a.png");
	texture.Bind();


	va.Unbind();
	vb.Unbind();
	ib1.Unbind();
	ib2.Unbind();
	shader.Unbind();
	texture.Unbind();

	Renderer renderer;
	
	

	float alpha = 0, beta = 0;
	
	while (!glfwWindowShouldClose(window))
	{
		
		/* render here */
		renderer.Clear();


		texture.Bind(0);
		shader.SetUniform1i("u_Texture", 0);
		{
			alpha += 0.01;
			beta += 0.01;
			glm::vec3 cam(2*std::sin(alpha), 2.0f, 2*std::cos(alpha));
			//glm::vec3 cam(0.0f, 0.0f, 2.0f);
			//glm::vec3 angle(std::sin(beta), std::cos(beta), 0.0f);
			glm::vec3 angle(0.0f, 1.0f, 0.0f);

			glm::mat4 V = glm::lookAt( cam,glm::vec3( 0.f, 0.f, 0.f ), angle);
			glm::mat4 MVP	= P*V;
			shader.SetUniformMat4f("u_MVP", MVP);
			
			
			float x = ((alpha / (2*3.1416)) - static_cast<float>(static_cast<int>(alpha / (2*3.1416))));
			std::cout<<alpha<<" : "<<x<<std::endl;
			if (x < 0.5)
				renderer.Draw(va, ib1, shader);
			else
				renderer.Draw(va, ib2, shader);
			
			
			
			
		}
		
		
		
	
		



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
} // detele everything before OpenGL terminate	

	glfwTerminate();
	return 0;
}

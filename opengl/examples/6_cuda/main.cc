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
#include"CudaResource.h"

#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include<cmath>
#include<ctime>
#include<mutex>


#define HEIGHT 640
#define WIDTH 640


float pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;


float t=1;

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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	float positions[] = 
	{
		-1, -1, 0, 0, 0, //bottom left
		-1,  1, 0, 0, 1, //top left
		 1,  1, 0, 1, 1, //top right
		 1, -1, 0, 1, 0  //bottom right 
	};
	unsigned int indices[] = 
	{
		0, 1, 2,
		2, 3, 0
	};



	VertexArray va;
		VertexBuffer vb(20*sizeof(float));
		VertexBufferLayout layout;
		layout.Push_float(3);//2 floats of rectangle vertices
		layout.Push_float(2);//2 floats of texture coordinates
		va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);



	Shader shader("./resources/shaders/math.shader");
	shader.Bind();

	Texture texture("./resources/textures/world.png");
	texture.Bind();

	
	glm::mat4 Proj = glm::perspective(1.5708f, (float)HEIGHT / (float)WIDTH, 0.0f, 100.0f);
	glm::mat4 View = glm::lookAt(glm::vec3(0.0f,0.0f,2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model(1.0f);

	glm::mat4 MVP = Proj * View * Model;
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", MVP);


	vb.setData((void*)&positions[0], 20*sizeof(float));





	void device_set_dynamic_position(cudaStream_t stream, float *d_arr, float t);
	CudaResource CR(&vb);
	CR.Map();

	Renderer renderer;
	float FPS=0;
	while (!glfwWindowShouldClose(window))
	{
		std::clock_t t1 = std::clock();
		/* render here */
		renderer.Clear();




		device_set_dynamic_position(CR.getStream(), reinterpret_cast<float*>(CR.getPointer()), t);
		CR.syncStream();
		t = 1;





		renderer.Draw(va, ib, shader);
		glfwSwapBuffers(window);
		glfwPollEvents();

		//glfwWaitEvents();
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		glfwSetKeyCallback(window, key_callback);
		std::clock_t t2 = std::clock();
                FPS = 0.99*FPS + 0.01*static_cast<float>(CLOCKS_PER_SEC)/(t2-t1);
		std::cout<<"FPS = "<<FPS<<std::endl;
	}
	CR.Unmap();
	
} // detele everything before OpenGL terminate	

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS or action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_RIGHT)
		{
		}
		if (key == GLFW_KEY_LEFT) 
		{
		}
		if (key == GLFW_KEY_UP) 
		{
			t+= 0.1*t;
		}
		if (key == GLFW_KEY_DOWN) 
		{
			t-= 0.1*t;
		}
	}
}


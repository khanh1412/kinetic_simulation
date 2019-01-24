#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>


#include"Renderer.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"
#include"VertexBufferLayout.h"
#include"Texture.h"
#include"CudaResource.h"
#include"CudaBuffer.h"

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
		0, 1, 2, //top left triangle
		2, 3, 0  //bottom right triangle
	};
	float norms[] =
	{
		0, 0, 1, //top left triangle
		0, 0,-1  //bottom right triangle
	};



	VertexArray va;
		VertexBuffer vb(20*sizeof(float));
		VertexBufferLayout layout;
		layout.Push_float(3);//2 floats of rectangle vertices
		layout.Push_float(2);//2 floats of texture coordinates
		va.AddBuffer(vb, layout);

	IndexBuffer ib(6);
	CudaBuffer all_ib(&indices[0], 6*sizeof(unsigned int));
	CudaBuffer nb(&norms[0], 6);



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





	void device_set_dynamic_positions(cudaStream_t stream, float *d_arr, float t);
	void device_set_dynamic_indices(cudaStream_t stream, unsigned int *d_all_ib, unsigned int *d_ib);
	CudaResource VB(&vb);
	CudaResource ALL_IB(&all_ib);
	CudaResource IB(&ib);
	CudaResource NB(&nb);
	VB.Map();
	ALL_IB.Map();
	IB.Map();
	NB.Map();

	std::cout<<"vb size = "		<<VB.getSize()		<<std::endl;
	std::cout<<"all_ib size = "	<<ALL_IB.getSize()	<<std::endl;
	std::cout<<"ib size = "		<<IB.getSize()		<<std::endl;
	std::cout<<"nb size = "		<<NB.getSize()		<<std::endl;




//	__builtin_trap();

	Renderer renderer;
	float FPS=0;
	while (!glfwWindowShouldClose(window))
	{
		std::clock_t t1 = std::clock();
		/* render here */
		renderer.Clear();




		device_set_dynamic_positions(VB.getStream(), reinterpret_cast<float*>(VB.getPointer()), t);
		device_set_dynamic_indices(NB.getStream(),
				reinterpret_cast<unsigned int*>(ALL_IB.getPointer()),
				reinterpret_cast<unsigned int*>(IB.getPointer()));
		VB.syncStream();
		ALL_IB.syncStream();
		IB.syncStream();
		NB.syncStream();
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
		//__builtin_trap();
	}
	VB.Unmap();
	NB.Unmap();
	
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


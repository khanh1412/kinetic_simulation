#include"Engine.h"
#include"Sphere.h"
#include"Rectangle.h"
#include"Cylinder.h"
#include<iostream>
#include<cmath>
int main()
{
	Engine E(640, 480, "world");
	
	auto center = glm::vec3({0.0f,0.0f,0.0f});
	auto vec1 = glm::vec3({0.0f,10.0f,0.0f});
	auto vec2 = glm::vec3({10.0f,0.0f,0.0f});


	Object *grass = new Rectangle(center, vec1, vec2);
	grass->genTexture("./resources/textures/grass.png");
	


	glfwSwapInterval(1);

	while (!E.isClosed())
	{

		E.clear();
			

		E.setCam(0, 0, 20);
		E.setCenter(0, 0, 0);
		E.setUp(0,1,0);
		E.setPov(1.0);
		E.draw(grass);

		E.swapBuffers();
		E.pollEvents();
		//__builtin_trap();
	}

}

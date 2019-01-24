#include"Environment.h"
#include<iostream>
#include<cstring>
int main(int argc, char **argv)
{
	double dt = (argc < 2) ? 0.0002 : std::atof(argv[1]);

	Environment env(dt);

	std::vector<Object*> AllObjects;
	Plane p({0,0,0});
	Sphere s({0,0,1}, 0.001);
	AllObjects.push_back(&p);
	AllObjects.push_back(&s);


	for (size_t i=0; i<AllObjects.size(); ++i)
		env.pushObject(AllObjects[i]);
	return 0;
}

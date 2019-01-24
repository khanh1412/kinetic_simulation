#include"Environment.h"
#include<iostream>
#include<cstring>
int main(int argc, char **argv)
{
	double dt = (argc < 2) ? 0.0002 : std::atof(argv[1]);

	Environment env(dt);

	Plane p({0,0,0});
	Sphere s({0,0,1}, 0.001);

	env.pushObject(&s);
	env.pushObject(&p);

	while (true)
		env.nextState();


	return 0;
}

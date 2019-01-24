#include"Environment.h"
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
int main(int argc, char **argv)
{
	double dt = (argc < 2) ? 0.00001 : std::atof(argv[1]);

	Environment env(dt);

	Plane p({0,0,0});
	Sphere s1({0,0,1}, 0.1, 1.0);
	Sphere s2({0,0,2}, 0.1, 2.0);

	env.pushObject(&s1);
	env.pushObject(&s2);
	env.pushObject(&p);

	std::ofstream out("./data.csv");
	out<<"time,x1,y1,z1,x2,y2,z2"<<std::endl;

	while (env.timer < 10)
	{
		std::cout << "\033[2J\033[1;1H";
		env.nextState();
		out<<env.timer;
		out<<","<<s1.pos.x<<","<<s1.pos.y<<","<<s1.pos.z;
		out<<","<<s2.pos.x<<","<<s2.pos.y<<","<<s2.pos.z;
		out<<std::endl;

	}


	return 0;
}

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
	Sphere s1({0,0,1}, 0.001, 1.0);
	Sphere s2({0,0,2}, 0.001, 1.0);
	Sphere s3({0,0,3}, 0.001, 1.0);

	env.pushObject(&s1);
	env.pushObject(&s2);
	env.pushObject(&s3);
	env.pushObject(&p);

	std::ofstream out("./data.csv");
	out<<"time,z0,z1,z2,z3"<<std::endl;

	while (env.timer < 5)
	{
		std::cout << "\033[2J\033[1;1H";
		env.nextState();
		out<<env.timer;
		out<<","<<0<<","<<s1.pos.z<<","<<s2.pos.z<<","<<s3.pos.z;
		out<<std::endl;

	}


	return 0;
}

#ifndef _SPHERE_H_
#define _SPHERE_H_
#include"Engine.h"
class Sphere: public Object
{
	private:
		float pos[3];
		float r;
		float d;
		float pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;

		int n;
	protected:
		int getPositions(float*& positions);
		int getIndices(float *cam, unsigned int*& indices);
	public:
		Sphere(float x=0.0f, float y=0.0f, float z=0.0f, float r=1.0f, float d=0.01f);
		~Sphere();
};
#endif

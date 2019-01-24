#ifndef _CYLINDER_H_
#define _CYLINDER_H_
#include"Engine.h"
class Cylinder: public Object
{
	private:
		float pos1[3];
		float pos2[3];
		float r;
		float pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
		int nr;
		float e1[3];
		float e2[3];
		float d;
	protected: 
                int getPositions(float*& positions);
                int getIndices(float *cam, unsigned int*& indices);
	public:
		Cylinder(float x1=0, float y1=0, float z1=0, float x2=0, float y2=0, float z2=1, float r=1, float d=0.01f);
		~Cylinder();
};
#endif
